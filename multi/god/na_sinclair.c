// 作者：匿名用户
// 链接：https://www.zhihu.com/question/27037437/answer/35230008
// 来源：知乎
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

/***************** q3.h **********************/
    #include <stdint.h>
    #include <stdlib.h>
    #include <emmintrin.h>
     
    #ifndef likely
    #define likely(x)       __builtin_expect((x), 1)
    #endif
     
    #ifndef unlikely
    #define unlikely(x)     __builtin_expect((x), 0)
    #endif
     
     
    #define QSZ     (1024 * 1)
    #define QMSK    (QSZ - 1)
     
    struct msg {
            uint64_t dummy;
    };
     
    #define CACHE_LINE_SIZE         64
     
    struct queue {
            struct {
                    uint32_t mask;
                    uint32_t size;
                    volatile uint32_t head;
                    volatile uint32_t tail;
            } p;
            char pad[CACHE_LINE_SIZE - 4 * sizeof(uint32_t)];
     
            struct {
                    uint32_t mask;
                    uint32_t size;
                    volatile uint32_t head;
                    volatile uint32_t tail;
            } c;
            char pad2[CACHE_LINE_SIZE - 4 * sizeof(uint32_t)];
     
            void              *msgs[0];
    };
     
    static inline struct queue *
    qinit(void)
    {
            struct queue *q = calloc(1, sizeof(*q) + QSZ * sizeof(void *));
            q->p.size = q->c.size = QSZ;
            q->p.mask = q->c.mask = QMSK;
     
            return q;
    }
     
     
    static inline int
    push(struct queue *q, void *m)
    {
            uint32_t head, tail, mask, next;
            int ok;
     
            mask = q->p.mask;
     
            do {
                    head = q->p.head;
                    tail = q->c.tail;
                    if ((mask + tail - head) < 1U)
                            return -1;
                    next = head + 1;
                    ok = __sync_bool_compare_and_swap(&q->p.head, head, next);
            } while (!ok);
     
            q->msgs[head & mask] = m;
            asm volatile ("":::"memory");
     
            while (unlikely((q->p.tail != head)))
                    _mm_pause();
     
            q->p.tail = next;
     
            return 0;
    }
     
    static inline void *
    pop(struct queue *q)
    {
            uint32_t head, tail, mask, next;
            int ok;
            void *ret;
     
            mask = q->c.mask;
     
            do {
                    head = q->c.head;
                    tail = q->p.tail;
                    if ((tail - head) < 1U)
                            return NULL;
                    next = head + 1;
                    ok = __sync_bool_compare_and_swap(&q->c.head, head, next);
            } while (!ok);
     
            ret = q->msgs[head & mask];
            asm volatile ("":::"memory");
     
            while (unlikely((q->c.tail != head)))
                    _mm_pause();
     
            q->c.tail = next;
     
            return ret;
    }

/**************** q.h *************************/

    #include <stdint.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
     
    struct msg {
            struct msg *next;
    };
     
    struct queue {
            uint32_t head;
            uint32_t tail;
            struct msg      **msgs;
            struct msg      *list;
    };
     
    #define CNT     0x10000
    #define GP(x)   (x % (CNT))
     
    static inline struct queue *
    qinit(void)
    {
            struct queue *q = malloc(sizeof(*q));
     
            bzero(q, sizeof(*q));
            q->msgs = calloc(sizeof(struct msg *), CNT);
     
            return q;
    }
     
    static inline int
    push(struct queue *q, struct msg *m)
    {
            uint32_t tail = GP(__sync_fetch_and_add(&q->tail, 1));
     
            if (!__sync_bool_compare_and_swap(&q->msgs[tail], NULL, m)) {
                    struct msg *last;
                    do {
                            last = q->list;
                            m->next = last;
                    } while (!__sync_bool_compare_and_swap(&q->list, last, m));
            }
            return 0;
    }
     
    static inline struct msg *
    pop(struct queue *q)
    {
            uint32_t head = q->head;
            uint32_t h2;
            struct msg *list;
     
            if (head == q->tail)
                    return NULL;
     
            h2 = GP(head);
            list = q->list;
     
            if (list) {
                    struct msg *n = list->next;
                    if (__sync_bool_compare_and_swap(&q->list, list, n)) {
                            list->next = NULL;
                            push(q, list);
                    }
            }
            struct msg *m = q->msgs[h2];
            if (!m)
                    return NULL;
            if (!__sync_bool_compare_and_swap(&q->head, head, head + 1))
                    return NULL;
            if (!__sync_bool_compare_and_swap(&q->msgs[h2], m, NULL))
                    return NULL;
     
            return m;
    }

/************ qlock.h ******************/

    #include <stdlib.h>
     
    struct msg {
            struct msg *next;
    };
     
    struct queue {
            struct msg *head;
            struct msg *tail;
            int lock;
    };
     
    #define LOCK(q) while (__sync_lock_test_and_set(&(q)->lock,1)) {}
    #define UNLOCK(q) __sync_lock_release(&(q)->lock);
     
    static inline struct queue *
    qinit(void)
    {
            struct queue *q = calloc(1, sizeof(*q));
            return q;
    }
     
    static inline int
    push(struct queue *q, struct msg *m)
    {
            LOCK(q)
            if (q->tail) {
                    q->tail->next = m;
                    q->tail = m;
            } else {
                    q->head = q->tail = m;
            }
            UNLOCK(q)
     
            return 0;
    }
     
    static inline struct msg *
    pop(struct queue *q)
    {
            struct msg *m;
     
            LOCK(q)
            m = q->head;
            if (m) {
                    q->head = m->next;
                    if (q->head == NULL) {
                            q->tail = NULL;
                    }
                    m->next = NULL;
            }
            UNLOCK(q)
     
            return m;
    }

/****************** a.c ***********************/
	

    #define _GNU_SOURCE
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <pthread.h>
    #include <sched.h>
     
    #include "q3.h"
    //#include "q.h"
    //#include "qlock.h"
     
    static struct msg *msgs;
     
     
    #define POP_CNT         7
    #define PUSH_CNT        7
     
    #define MSG_CNT         (PUSH_CNT * 1000000)
     
    static inline uint64_t
    rdtsc(void)
    {
        union {
            uint64_t tsc_64;
            struct {
                uint32_t lo_32;
                uint32_t hi_32;
            };
        } tsc;
     
        asm volatile("rdtsc" :
            "=a" (tsc.lo_32),
            "=d" (tsc.hi_32));
        return tsc.tsc_64;
    }
     
    static volatile int quit = 0;
    static volatile int pop_total = 0;
    static volatile int push_total = 0;
     
    static volatile uint64_t push_cycles = 0;
    static volatile uint64_t pop_cycles = 0;
     
     
    static void *
    pop_task(void *arg)
    {
            struct queue *q = arg;
            uint64_t start = rdtsc();
            int cnt = 0;
     
            while (!quit)
                    cnt += !!pop(q);
     
            pop_cycles += rdtsc() - start;
            pop_total += cnt;
     
            return NULL;
    }
     
    static void *
    push_task(void *arg)
    {
            struct queue *q = arg;
            uint64_t start = rdtsc();
            int i;
     
            for (i = 0; i < MSG_CNT / PUSH_CNT; i++)
                    while (push(q, msgs + i) == -1);
     
            push_cycles += rdtsc() - start;
            push_total += MSG_CNT / PUSH_CNT;
            if (push_total == MSG_CNT)
                    quit = 1;
     
            return NULL;
    }
     
    /* topology for Xeon E5-2670 Sandybridge */
    static const int socket_top[] = {
        1,  2,  3,  4,  5,  6,  7,
        16, 17, 18, 19, 20, 21, 22, 23,
        8,  9,  10, 11, 12, 13, 14, 15,
        24, 25, 26, 27, 28, 29, 30, 31
    };
     
    #define CORE_ID(i)      socket_top[(i)]
     
     
    static int
    start_thread(int id,
                 void *(*cb)(void *),
                 void *arg,
                 pthread_t *tid)
    {
            pthread_t kid;
            pthread_attr_t attr;
            cpu_set_t cpuset;
            int core_id;
     
            if (id < 0 || id >= sizeof(socket_top) / sizeof(int))
                    return -1;
     
            if (pthread_attr_init(&attr))
                    return -1;
     
            CPU_ZERO(&cpuset);
            core_id = CORE_ID(id);
            CPU_SET(core_id, &cpuset);
     
            if (pthread_create(&kid, &attr, cb, arg))
                    return -1;
            if (pthread_setaffinity_np(kid, sizeof(cpu_set_t), &cpuset))
                    return -1;
     
            if (tid)
                    *tid = kid;
     
            return 0;
    }
     
    static int
    setaffinity(int core_id)
    {
            cpu_set_t cpuset;
            pthread_t me = pthread_self();
     
            CPU_ZERO(&cpuset);
            CPU_SET(core_id, &cpuset);
     
            if (pthread_setaffinity_np(me, sizeof(cpu_set_t), &cpuset))
                    return -1;
     
            return 0;
    }
     
    int
    main(void)
    {
            struct queue *q = qinit();
            int i;
            pthread_t kids[POP_CNT + PUSH_CNT];
     
            setaffinity(0);
     
            msgs = calloc(MSG_CNT, sizeof(struct msg));
            for (i = 0; i < POP_CNT; i++)
                    start_thread(i, pop_task, q, &kids[i]);
            for (; i < POP_CNT + PUSH_CNT; i++)
                    start_thread(i, push_task, q, &kids[i]);
            for (i = 0; i < POP_CNT + PUSH_CNT; i++)
                    pthread_join(kids[i], NULL);
     
            printf("pop total: %d\n", pop_total);
            printf("pop cycles/msg: %lu\n", pop_cycles / pop_total);
            printf("push cycles/msg: %lu\n", push_cycles / MSG_CNT);
     
            return 0;
    }

/***************** a2.c ********************/

    #define _GNU_SOURCE
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <pthread.h>
    #include <sched.h>
     
    #include "q3.h"
    //#include "q.h"
    //#include "qlock.h"
     
    static struct msg *msgs;
     
     
    #define POP_CNT     7
    #define PUSH_CNT    7
     
    #define MSG_CNT     (PUSH_CNT * 1000000)
     
    static inline uint64_t
    rdtsc(void)
    {
        union {
            uint64_t tsc_64;
            struct {
                uint32_t lo_32;
                uint32_t hi_32;
            };
        } tsc;
     
        asm volatile("rdtsc" :
            "=a" (tsc.lo_32),
            "=d" (tsc.hi_32));
        return tsc.tsc_64;
    }
     
    static volatile int quit = 0;
    static volatile int pop_total = 0;
    static volatile int push_total = 0;
     
    static volatile uint64_t push_cycles = 0;
    static volatile uint64_t pop_cycles = 0;
     
     
    static void *
    pop_task(void *arg)
    {
        struct queue *q = arg;
        uint64_t start = rdtsc();
        int cnt = 0;
     
        while (!quit)
            cnt += !!pop(q);
     
        pop_cycles += rdtsc() - start;
        pop_total += cnt;
     
        return NULL;
    }
     
    static void *
    pop_flush_task(void *arg)
    {
        struct queue *q = arg;
        uint64_t start = rdtsc();
     
        while (!quit) {
            __sync_fetch_and_add(&pop_total, !!pop(q));
            if (pop_total == MSG_CNT)
                quit = 1;
        }
     
        pop_cycles += rdtsc() - start;
     
        return NULL;
    }
     
    static void *
    push_task(void *arg)
    {
        struct queue *q = arg;
        uint64_t start = rdtsc();
        int i;
     
        for (i = 0; i < MSG_CNT / PUSH_CNT; i++)
            while (push(q, msgs + i) == -1);
     
        push_cycles += rdtsc() - start;
        push_total += MSG_CNT / PUSH_CNT;
        if (push_total == MSG_CNT)
            quit = 1;
     
        return NULL;
    }
     
    /* topology for Xeon E5-2670 Sandybridge */
    static const int socket_top[] = {
        1,  2,  3,  4,  5,  6,  7,
        16, 17, 18, 19, 20, 21, 22, 23,
        8,  9,  10, 11, 12, 13, 14, 15,
        24, 25, 26, 27, 28, 29, 30, 31
    };
     
    #define CORE_ID(i)      socket_top[(i)]
     
    static int
    start_thread(int id,
                 void *(*cb)(void *),
                 void *arg,
                 pthread_t *tid)
    {
        pthread_t kid;
        pthread_attr_t attr;
        cpu_set_t cpuset;
        int core_id;
     
        if (id < 0 || id >= sizeof(socket_top) / sizeof(int))
            return -1;
     
        if (pthread_attr_init(&attr))
            return -1;
     
        CPU_ZERO(&cpuset);
        core_id = CORE_ID(id);
        CPU_SET(core_id, &cpuset);
     
        if (pthread_create(&kid, &attr, cb, arg))
            return -1;
        if (pthread_setaffinity_np(kid, sizeof(cpu_set_t), &cpuset))
            return -1;
     
        if (tid)
            *tid = kid;
     
        return 0;
    }
     
    static int
    setaffinity(int core_id)
    {
        cpu_set_t cpuset;
        pthread_t me = pthread_self();
     
        CPU_ZERO(&cpuset);
        CPU_SET(core_id, &cpuset);
     
        if (pthread_setaffinity_np(me, sizeof(cpu_set_t), &cpuset))
            return -1;
     
        return 0;
    }
     
    int
    main(void)
    {
        struct queue *q = qinit();
        int i;
        pthread_t kids[POP_CNT + PUSH_CNT];
     
        setaffinity(0);
     
        msgs = calloc(MSG_CNT, sizeof(struct msg));
        for (i = 0; i < POP_CNT; i++)
            start_thread(i, pop_task, q, &kids[i]);
        for (; i < POP_CNT + PUSH_CNT; i++)
            start_thread(i, push_task, q, &kids[i]);
        for (i = 0; i < POP_CNT + PUSH_CNT; i++)
            pthread_join(kids[i], NULL);
     
        quit = 0;
     
        if (pop_total < MSG_CNT) {
            printf("flushing: %d\n", MSG_CNT - pop_total);
            for (i = 0; i < POP_CNT; i++)
                start_thread(i, pop_flush_task, q, &kids[i]);
            for (i = 0; i < POP_CNT; i++)
                pthread_join(kids[i], NULL);
        }
     
        printf("pop total: %d\n", pop_total);
        printf("pop cycles/msg: %lu\n", pop_cycles / pop_total);
        printf("push cycles/msg: %lu\n", push_cycles / MSG_CNT);
     
        return 0;
    }

/*************** a3.c ******************/
	

    #define _GNU_SOURCE
     
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <pthread.h>
    #include <sched.h>
    #include <emmintrin.h>
     
    #include "q3.h"
    //#include "q.h"
    //#include "qlock.h"
     
    static struct msg *msgs;
    static int *msg_flags;
     
    #define POP_CNT     7
    #define PUSH_CNT    7
     
    #define MSG_CNT     (PUSH_CNT * 1000000)
     
    static inline uint64_t
    rdtsc(void)
    {
        union {
            uint64_t tsc_64;
            struct {
                uint32_t lo_32;
                uint32_t hi_32;
            };
        } tsc;
     
        asm volatile("rdtsc" :
            "=a" (tsc.lo_32),
            "=d" (tsc.hi_32));
        return tsc.tsc_64;
    }
     
    static volatile int quit = 0;
    static volatile int pop_total = 0;
    static volatile int push_total = 0;
     
    static volatile uint64_t push_cycles = 0;
    static volatile uint64_t pop_cycles = 0;
     
    #define delay(c) do {                   \
        if ((c) == 0) break;                \
        uint64_t start = rdtsc();           \
        uint64_t now = start;               \
        while (now - start < (c)) {         \
            _mm_pause();                    \
            now = rdtsc();                  \
        }                                   \
    } while (0)
     
     
    static void *
    pop_task(void *arg)
    {
        struct queue *q = arg;
        uint64_t start = rdtsc();
        int cnt = 0;
     
        while (!quit) {
            struct msg *m = pop(q);
            if (m) {
                cnt++;
                msg_flags[(m - msgs)] = 1;
            }
            //delay(2000);
        }
     
        pop_cycles += rdtsc() - start;
        __sync_fetch_and_add(&pop_total, cnt);
     
        return NULL;
    }
     
    static void *
    pop_flush_task(void *arg)
    {
        struct queue *q = arg;
        uint64_t start = rdtsc();
     
        while (!quit) {
            struct msg *m = pop(q);
            if (m) {
                __sync_fetch_and_add(&pop_total, 1);
                msg_flags[(m - msgs)] = 1;
            }
            if (pop_total == MSG_CNT)
                quit = 1;
        }
     
        pop_cycles += rdtsc() - start;
     
        return NULL;
    }
     
    static volatile int push_msg_idx = 0;
     
    static void *
    push_task(void *arg)
    {
        struct queue *q = arg;
        uint64_t start = rdtsc();
        int i;
     
        for (i = 0; i < MSG_CNT / PUSH_CNT; i++) {
            int idx = __sync_fetch_and_add(&push_msg_idx, 1);
            while (push(q, msgs + idx) == -1);
        }
     
        push_cycles += rdtsc() - start;
        __sync_fetch_and_add(&push_total,  MSG_CNT / PUSH_CNT);
        if (push_total == MSG_CNT)
            quit = 1;
     
        return NULL;
    }
     
    /* topology for Xeon E5-2670 Sandybridge */
    static const int socket_top[] = {
        1,  2,  3,  4,  5,  6,  7,
        16, 17, 18, 19, 20, 21, 22, 23,
        8,  9,  10, 11, 12, 13, 14, 15,
        24, 25, 26, 27, 28, 29, 30, 31
    };
     
    #define CORE_ID(i)      socket_top[(i)]
     
     
    static int
    start_thread(int id,
                 void *(*cb)(void *),
                 void *arg,
                 pthread_t *tid)
    {
        pthread_t kid;
        pthread_attr_t attr;
        cpu_set_t cpuset;
        int core_id;
     
        if (id < 0 || id >= sizeof(socket_top) / sizeof(int))
            return -1;
     
     
        if (pthread_attr_init(&attr))
            return -1;
     
        CPU_ZERO(&cpuset);
        core_id = CORE_ID(id);
        CPU_SET(core_id, &cpuset);
     
        if (pthread_create(&kid, &attr, cb, arg))
            return -1;
        if (pthread_setaffinity_np(kid, sizeof(cpu_set_t), &cpuset))
            return -1;
     
        if (tid)
            *tid = kid;
     
        return 0;
    }
     
    static int
    setaffinity(int core_id)
    {
        cpu_set_t cpuset;
        pthread_t me = pthread_self();
     
        CPU_ZERO(&cpuset);
        CPU_SET(core_id, &cpuset);
     
        if (pthread_setaffinity_np(me, sizeof(cpu_set_t), &cpuset))
            return -1;
     
        return 0;
    }
     
    int
    main(void)
    {
        struct queue *q = qinit();
        int i;
        pthread_t kids[POP_CNT + PUSH_CNT];
     
        setaffinity(0);
     
        msgs = calloc(MSG_CNT, sizeof(struct msg));
        msg_flags = calloc(MSG_CNT, sizeof(int));
     
        for (i = 0; i < POP_CNT; i++)
            start_thread(i, pop_task, q, &kids[i]);
        for (; i < POP_CNT + PUSH_CNT; i++)
            start_thread(i, push_task, q, &kids[i]);
        for (i = 0; i < POP_CNT + PUSH_CNT; i++)
            pthread_join(kids[i], NULL);
     
        quit = 0;
     
        if (pop_total < MSG_CNT) {
            printf("flushing: %d\n", MSG_CNT - pop_total);
            for (i = 0; i < POP_CNT; i++)
                start_thread(i, pop_flush_task, q, &kids[i]);
            for (i = 0; i < POP_CNT; i++)
                pthread_join(kids[i], NULL);
        }
     
        printf("pop total: %d\n", pop_total);
        printf("pop cycles/msg: %lu\n", pop_cycles / pop_total);
        printf("push cycles/msg: %lu\n", push_cycles / MSG_CNT);
        printf("push idx: %d\n", push_msg_idx);
     
        /* sanity test */
        int miss = 0;
        for (i = 0; i < MSG_CNT; i++) {
            if (msg_flags[i] != 1) {
                miss++;
            }
        }
        printf("total %d miss\n", miss);
     
        return 0;
    }
