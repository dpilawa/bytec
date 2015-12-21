/*

    Memory manager
    Simple implementation of buddy blocks memory allocation
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

#include "mm.h"
#include "klibc.h"

/* This is the total memory pool and it needs to be allocated (e.g. statically)
   by a higher lever program (e.g. OS)                                          */
memblk_t *__kern_mm_pool;

/* Set memory block flags                                                       */
extern void __kern_mm_setblk(memblk_t* __blk, unsigned int __size, 
                        unsigned int  __allocated, unsigned int __leaf, unsigned int __lrr)
{
    __blk->size = __size;
    __blk->allocated = __allocated;
    __blk->leaf = __leaf;
    __blk->lrr = __lrr;
}

/* Initialize memory pool and create root block                                 */
extern void  __kern_mm_init(char* __pool, unsigned int __size)
{
    __kern_mm_pool = (memblk_t*)__pool;
    __kern_mm_setblk(__kern_mm_pool, __size - sizeof(memblk_t), 0, 1, MM_ROOT);
}

/* Find a block in current tree best fitting requested size                     
   return a pointer to this block or zero if no fit found                       */ 
extern memblk_t* __kern_mm_getbestfit(memblk_t* __blk, unsigned int __size)
{
    memblk_t *blk_l, *blk_r;

    /* reached a leaf, return a block if free or 0 otherwise                    */
    if (LEFT(__blk) == 0 && RIGHT(__blk) == 0)
    {   
        if (__blk->size >= __size && __blk->allocated == 0)
        {
            return __blk;
        }
        else
        {
            return 0;
        }
    }
    else
    /* not a leaf, look recursively in subtrees                                 */
    {
        blk_l = __kern_mm_getbestfit(LEFT(__blk), __size);
        blk_r = __kern_mm_getbestfit(RIGHT(__blk), __size);
        if (blk_l && blk_r)
        {
            return blk_l->size <= blk_r->size ? blk_l : blk_r;
        }
        else if (blk_l)
        {
            return blk_l;
        }
        else if (blk_r)
        {
            return blk_r;
        }
        else 
        {
            return 0;
        }  
    }
}

/* Split a block into two buddies and create headers for new blocks.                                               
   If the split renders one block larger by 1 byte, this block goes 
   to the right node.                                                           
   
   This is recursive - splitting continues until block cannot be further
   divided (smaller than MIN_BLK) or would not fit the requested size.          */
extern memblk_t*  __kern_mm_split(memblk_t* __blk, unsigned int __size)
{
    unsigned int size_l, size_r;
    unsigned int s1, s2;

    s1 = __blk->size / 2 - sizeof(memblk_t);
    s2 = __blk->size - __blk->size / 2 - sizeof(memblk_t);

    /* larger block to the right node                                           */
    size_l = MIN(s1,s2);
    size_r = MAX(s1,s2);

    /* split further as long as block is not smaller than MIN_BLK and 
       can fit the requested size                                               */
    if (size_l >= MIN_BLK && size_r >= MIN_BLK && (size_l >= __size || size_r >= __size))
    {
        __blk->leaf = 0;
        __kern_mm_setblk(LEFT(__blk), size_l, 0, 1, MM_LEFT);
        __kern_mm_setblk(RIGHT(__blk), size_r, 0, 1, MM_RIGHT);
        if (size_l >= __size)
        {   
            return __kern_mm_split(LEFT(__blk), __size);
        }
        else
        {
            return __kern_mm_split(RIGHT(__blk), __size);
        }
    }
    else 
    {
        return __blk;
    }
}

/* Allocate memory block of reqested size.
   This fist finds a best match in current tree, without modifying it.
   Then the best-fit block is further split as long as it can still hold the
   requested size, and is larger than predefined miniumum.                      */
extern char* __kern_mm_alloc(unsigned int __size)
{
    memblk_t *freeblk;

    if (freeblk = __kern_mm_getbestfit(__kern_mm_pool, __size))
    {
        freeblk = __kern_mm_split(freeblk, __size);
        __kern_mm_setblk(freeblk, freeblk->size, 1, 1, freeblk->lrr);
        return (char*)((char*)(freeblk) + sizeof(memblk_t));
    }
    else
    {
        return 0;
    }
}

/* Colaesce a block with its buddy.
   Search for parent and check if buddies can be merged.
   If yes, recursively coalesce the parent with its buddy.                      */
extern void  __kern_mm_coalesce(memblk_t* __blk)
{
    memblk_t *parent;
    
    if (parent = PARENT(__blk))
    {
        if (LEFT(parent)->allocated == 0 && LEFT(parent)->leaf && \
            RIGHT(parent)->allocated == 0 && RIGHT(parent)->leaf)
        {
            __kern_mm_setblk(parent, parent->size, 0, 1, parent->lrr);
            __kern_mm_coalesce(parent);
        }
    }
}

/* Free an allocated memory block, then attempt merging free blocks.
   Return 1 if block freed, zero otherwise.                                     */
extern int __kern_mm_free(char* __ptr)
{
    memblk_t *blk;

    blk = (memblk_t*)(__ptr - sizeof(memblk_t));
    if (blk->allocated && blk->leaf)
    {
        __kern_mm_setblk(blk, blk->size, 0, 1, blk->lrr);
        __kern_mm_coalesce(blk);
        return 1;
    }
    else
    {
        return 0;
    }
}

/* For debugging purposes only - print current allocation tree                  */
extern void  __kern_mm_print_memblk(memblk_t* __blk, unsigned int __depth)
{
    int i;
    
    for (i = 0; i < __depth; i++)
    {
        kprintf(" ");
    }

    kprintf("[0x%04x:0x%04x %u bytes", 
    (int)(__blk), (int)((int)(__blk) + sizeof(memblk_t) + __blk->size), __blk->size);    
    
    if (__blk->allocated)
    {
        kprintf(" allocated]\n");
    }
    else if (LEFT(__blk) == 0 && RIGHT(__blk) == 0)
    {
        kprintf(" unallocated]\n");
    }
    else
    {
        kprintf("]\n");
        __kern_mm_print_memblk(LEFT(__blk), __depth+2);
        __kern_mm_print_memblk(RIGHT(__blk), __depth+2);
    }
}

