/*

    Physical memory support routines
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

enum {PM_FREE, PM_USED};

/* memory block definition                                                  */
typedef struct mempage {
    unsigned char pageno;
    unsigned char status;
} mempage_t;

/* externs                                                                  */
extern void  __kern_pmem_init(void);

