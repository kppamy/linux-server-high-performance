#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
// #include <malloc.h>
size_t  heap_malloc_total, heap_free_total,
                mmap_total, mmap_count;
void print_info()
{
        struct mallinfo mi = mallinfo();
        printf("count by itself:\n");
        printf("\theap_malloc_total=%lu heap_free_total=%lu heap_in_use=%lu\n\
\tmmap_total=%lu mmap_count=%lu\n",
                heap_malloc_total*1024, heap_free_total*1024, heap_malloc_total*1024 - heap_free_total*1024,
                mmap_total*1024, mmap_count);
        printf("count by mallinfo:\n");
        printf("\theap_malloc_total=%lu heap_free_total=%lu heap_in_use=%lu\n\
\tmmap_total=%lu mmap_count=%lu\n",
                mi.arena, mi.fordblks, mi.uordblks,
                mi.hblkhd, mi.hblks);
        printf("from malloc_stats:\n");
        malloc_stats();
}

#define ARRAY_SIZE 200
int main(int argc, char** argv)
{
        char** ptr_arr[ARRAY_SIZE];
        int i;
        for( i = 0; i < ARRAY_SIZE; i++) {
                ptr_arr[i] = malloc(i * 1024);
                if ( i < 128)
                        heap_malloc_total += i;
                else {
                        mmap_total += i;
                        mmap_count++;
                }

        }
        print_info();
        for( i = 0; i < ARRAY_SIZE; i++) {
                if ( i % 2 == 0)
                        continue;
                free(ptr_arr[i]);
                if ( i < 128)
                        heap_free_total += i;
                else {
                        mmap_total -= i;
                        mmap_count--;
                }
        }
        printf("\nafter free\n");
        print_info();
        return 1;
}