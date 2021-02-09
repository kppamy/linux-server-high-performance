/**
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};


/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define CHUNKSIZE 1<<12 // 4k
#define WSIZE 4
#define DSIZE 8

//  size is aligned 8， so the last bit will always be 0
#define PACK(size,alloc) ((size)| (alloc))

#define GET(p) (*(unsigned int*)(p))
#define PUT(p,val) (*(unsigned int*)(p)=(val))

#define GET_SIZE(p)  (GET(p) & ~0x7) 
#define GET_ALLOC(p) (GET(p) & 0x1)


#define HDRP(bp) ((char*)bp - WSIZE)
#define FTRP(bp) ((char*)bp +  GET_SIZE(HDRP(bp) - DSIZE))

#define NEXT_BLKP(bp)  ((char*)bp +  GET_SIZE(HDRP(bp)) - WSIZE)
#define PREV_BLKP(bp)  ((char*)bp  - GET_SIZE((char*)bp - DSIZE))

static char* heap_listp=NULL; // stack? or heap?

size_t max(size_t a, size_t b){
    return a>b?a:b;
}

static void* first_fit(size_t asize){
   void* start=heap_listp;
   void* end = mem_heap_hi();
   while (start<end)
   {
       size_t size = GET_SIZE(start);
       if(size<asize){
           start=NEXT_BLKP(start);
       }else{
           return start;
       }
   }
   return -1;
}

static void* find_fit(size_t asize){
    return first_fit(asize);
}

static void place(void* bp, size_t asize){
    size_t bsize=GET_SIZE(bp);
    size_t left = bsize - asize;
    if (left > DSIZE + 8) // optimize?
    {
        PUT(HDRP(bp),PACK(asize,1));
        PUT(FTRP(bp),PACK(asize,1));
        PUT(HDRP(NEXT_BLKP(bp)),PACK(left,0));
        PUT(FTRP(NEXT_BLKP(bp)),PACK(left,0));
    }
    else{
        PUT(HDRP(bp),PACK(bsize,1));
        PUT(FTRP(bp),PACK(bsize,1));
    }
}

static void* coalesce(void *bp){
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t msize = GET_SIZE(HDRP(bp));
    if(prev_alloc && next_alloc){
        return bp;
    }
    else if(prev_alloc && !next_alloc){
        size_t nsize = GET_SIZE(HDRP(NEXT_BLKP(bp)));
        msize += nsize;
        PUT(HDRP(bp) , PACK(msize,0));
        PUT(FTRP(bp) , PACK(msize,0));
    }
    else if(!prev_alloc && next_alloc){
        size_t psize = GET_SIZE(HDRP(PREV_BLKP(bp)));
        msize += psize;
        bp = PREV_BLKP(bp);
        PUT(HDRP(bp) , PACK(msize,0));
        PUT(FTRP(bp) , PACK(msize,0));
    }
    else {

        size_t psize = GET_SIZE(HDRP(PREV_BLKP(bp)));
        msize += psize;
        size_t nsize = GET_SIZE(HDRP(NEXT_BLKP(bp)));
        msize += nsize;
        bp = PREV_BLKP(bp);
        PUT(HDRP(bp) , PACK(msize,0));
        PUT(FTRP(bp) , PACK(msize,0));
    }

    return bp;
}


static void* extend_heap(size_t words){
    size_t nsize=(words%2)?words*WSIZE:(words+1)*WSIZE;
    char* bp;
    if((long)(bp=mem_sbrk(nsize))==-1)
        return NULL;
    PUT(HDRP(bp),PACK(nsize,0)); // Free block header
    PUT(FTRP(bp),PACK(nsize,0)); // Free block footer
    PUT(HDRP(NEXT_BLKP(bp)),PACK(0,1)); // New Epilogue header
    return coalesce(bp);
}



/* 
 * mm_init - initialize the malloc package.
 * initialize the heap with a free block
 */
int mm_init(void)
{
    if((heap_listp=mem_sbrk(4*WSIZE))==(void*) -1)
        return -1;
    PUT(heap_listp, 0);// padding
    PUT(heap_listp+(1*WSIZE),PACK(DSIZE,1)); // prologue header
    PUT(heap_listp+(2*WSIZE),PACK(DSIZE,1));// prologue footer
    PUT(heap_listp+(3*WSIZE),PACK(0,1)); // epilogue header
    heap_listp+=(2*WSIZE);
    if(extend_heap(CHUNKSIZE/WSIZE)==NULL)
        return -1;
    return 0;
} 

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    int newsize = ALIGN(size + SIZE_T_SIZE);

    char* bp;
    if((bp=find_fit(newsize))!=NULL){
        place(bp,newsize);
        return bp;
    }

    void *p = mem_sbrk(newsize);
    if (p == (void *)-1)
        return NULL;
    
    // no fit found
    size_t extendsize=max(newsize, CHUNKSIZE);
    if((bp=extend_heap(extendsize/WSIZE))==NULL)
        return NULL;
    place(bp,newsize);
    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(ptr);
    PUT(HDRP(ptr),PACK(0,1));
    PUT(FTRP(ptr),PACK(0,1));
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;

    newptr = mm_malloc(size);
    if (newptr == NULL)
        return NULL;
    copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
    if (size < copySize)
        copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}
