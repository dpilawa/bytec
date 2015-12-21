/*

    Physical memory support routines
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

#include "pmem.h"
#include "kernel.h"
#include "klibc.h"

/* Root of memory pages array                                                   */
mempage_t *__kern_pmem_pages;

/* Check if memory address writable                                             */
int __kern_pmem_writable(char *__ptr)
{
    char b,b1,b2;

    b = *__ptr;
    b1 = b;
    b = b + 1;
    *__ptr = b;

    b = *__ptr;
    b = b - 1;
    b2 = b;
    *__ptr = b;
    
    if (b1 == b2)
    {
        return 1;
    }    
    else
    {
        return 0;
    }
}

/* Set memory page flags                                                        */
void __kern_pmem_setpage(unsigned char __pageno, unsigned char __status)
{
    mempage_t *page = (mempage_t*)(__kern_pmem_pages + __pageno);

    page->pageno = __pageno;
    page->status = __status;
}

/* Detect and initialize physical memory pages                                  */
void  __kern_pmem_init(void)
{

    unsigned char p,q;     /* page */
    unsigned int romsize = 0;
    unsigned int ramsize = 0;

    /* arbitrary pointer in the second page of kernel data space                */
    char *ptr = (char*)0xa000U;
    __kern_mempageset(KERN_REG_SUPER_DATAPAGE1, 0);
    
    /* loop through ROM                                                         */
    for (p=0; p<=255U && !__kern_pmem_writable(ptr); __kern_mempageset(KERN_REG_SUPER_DATAPAGE1, ++p));
    romsize = (unsigned int)p << 5;

    /* loop through RAM                                                         */
    for (q=p; q<=255U && __kern_pmem_writable(ptr); __kern_mempageset(KERN_REG_SUPER_DATAPAGE1, ++q));
    ramsize = ((unsigned int)q << 5) - romsize;

    /* restore default monitor DATAPAGE1                                        */
    __kern_mempageset(KERN_REG_SUPER_DATAPAGE1, 5);

    /* print memory size message                                                */
    kprintf("MEM:   %ukB ROM, %ukB RAM\n", romsize, ramsize);
    
    /* initialize memory pages map                                              */
    //__kern_pmem_pages = (mempage_t*)kmalloc(p * sizeof(mempage_t));
    //for (p=0; p<=5; p++)
    //{
    //    __kern_pmem_setpage(p, PM_USED);
    //}

}


