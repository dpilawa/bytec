/*

    Kernel routines
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

#include "kernel.h"

void __kern_isrvec(unsigned char __intno, void (*__israddr)(void)) 
{
    void (**ivec)(void) = KERN_IVEC;
    *(ivec+__intno) = __israddr;
}

void __kern_mempageset(unsigned int __pagereg, unsigned char __pageno)
{
    char *pagereg = (char*)__pagereg;
    *pagereg = __pageno;
}
