/*

    Memory manager
    Simple implementation of buddy blocks memory allocation
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

/* minimum allocatable memory block size                                    */
#define MIN_BLK 16

/* tree navigation macros                                                   */
#define LEFT(x)   ((x)->leaf ? 0 : (memblk_t*)((char*)(x) + sizeof(memblk_t)))
#define RIGHT(x)  ((x)->leaf ? 0 : (memblk_t*)((char*)(x) + 2 * sizeof(memblk_t) + ((memblk_t*)((char*)(x) + sizeof(memblk_t)))->size))
#define PARENT(x) (((x)->lrr == MM_ROOT) ? 0 : \
                  (((x)->lrr == MM_LEFT) ? \
                  ((memblk_t*)((char*)(x) - sizeof(memblk_t))) : \
                  ((memblk_t*)((char*)(x) - ((x)->size & ~1U) - 2 * sizeof(memblk_t)))))

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

enum {MM_LEFT, MM_RIGHT, MM_ROOT};

/* memory block definition                                                  */
typedef struct memblk {
    unsigned int size;
    unsigned int allocated:1;
    unsigned int leaf:1;
    unsigned int lrr:2;
} memblk_t;

/* memory pool root                                                         */
extern memblk_t* __kern_mm_pool;

/* externs                                                                  */
extern void  __kern_mm_init(char *__pool, unsigned int __size);
extern char* __kern_mm_alloc(unsigned int __size);
extern int   __kern_mm_free(char *__ptr);
extern void  __kern_mm_print_memblk(memblk_t *__blk, unsigned int __depth);

