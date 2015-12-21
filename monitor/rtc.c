/*

    RTC driver
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

#include "rtc.h"
#include "klibc.h"

/* detect and initialize RTC chip                               */
void __kern_rtc_init(void)
{
    char c1, c2, c3;
    unsigned char *reg = (unsigned char*)KERN_RTC;

    c1 = *(reg+KERN_RTC_CTL) | 0x0f;
    c2 = 0x56; /* any magic number */
    *(reg+KERN_RTC_ZERO) = c2;
    c2 = *(reg+KERN_RTC_ZERO);
    c3 = *(reg+KERN_RTC_FLGS) & KERN_RTC_FLGS_BVF;

    kprintf("RTC:   ");
    if (c1==0x0f && c2==0)
    {
        kprintf("found at 0x%04x (battery ", KERN_RTC);
        if (c3)
            kprintf("OK)");
        else
            kprintf("invalid)");
        kprintf("\n");
        *(reg+KERN_RTC_CTL) = KERN_RTC_CTL_NSTOP|KERN_RTC_CTL_24H;
    }
    else 
    {
        kprintf("not found\n");
    }
}

/* get current time                                             */
void __kern_rtc_tget(char *h, char *m, char *s)
{
    unsigned char val;
    unsigned char *reg = (unsigned char*)KERN_RTC;
    unsigned char ctl;

    /* set update transfer inhibit flag                         */
    ctl = *(reg+KERN_RTC_CTL);
    *(reg+KERN_RTC_CTL) |= KERN_RTC_CTL_UTI;

    /* get hours                                                */
    val = *(reg+KERN_RTC_HOUR);
    *h = 10 * ((val & 0x30)>>4) + (val & 0x0f);
    /* get minutes                                              */
    val = *(reg+KERN_RTC_MIN);
    *m = 10 * ((val & 0x70)>>4) + (val & 0x0f);
    /* get hours                                                */
    val = *(reg+KERN_RTC_SEC);
    *s = 10 * ((val & 0x70)>>4) + (val & 0x0f);

    /* restore control flags                                    */
    *(reg+KERN_RTC_CTL) = ctl;  

}

/* set time                                                     */
void __kern_rtc_tset(char h, char m, char s)
{
    char ch, cm, cs;
    unsigned char *reg = (unsigned char*)KERN_RTC;

    /* calculate BCD numbers                                    */
    ch = (((h/10)&0x03)<<4)|((h%10)&0x0f);
    cm = (((m/10)&0x07)<<4)|((m%10)&0x0f);
    cs = (((s/10)&0x07)<<4)|((s%10)&0x0f);

    *(reg+KERN_RTC_HOUR) = ch;
    *(reg+KERN_RTC_MIN) = cm;
    *(reg+KERN_RTC_SEC) = cs;
}

