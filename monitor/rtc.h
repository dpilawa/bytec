/*

    RTC driver
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

/* RTC base vector */
#define KERN_RTC 0x1020

/* RTC registers */
#define KERN_RTC_SEC  0x00        /* Seconds                                */
#define KERN_RTC_MIN  0x02        /* Minutes                                */
#define KERN_RTC_HOUR 0x04        /* Hours                                  */
#define KERN_RTC_FLGS 0x0d        /* Flags register                         */
#define KERN_RTC_CTL  0x0e        /* Control register                       */
#define KERN_RTC_ZERO 0x0f        /* non writable, reads zero               */

/* RTC flags */
#define KERN_RTC_FLGS_BVF  0x01   /* battery valid flag                     */
#define KERN_RTC_CTL_NSTOP 0x04   /* STOP bit (1 to turn RTC on)            */
#define KERN_RTC_CTL_UTI   0x08   /* update transfer inhibit                */
#define KERN_RTC_CTL_24H   0x02   /* 24/12 mode selector                    */

extern void __kern_rtc_init(void);
extern void __kern_rtc_tget(char *h, char *m, char *s);
extern void __kern_rtc_tset(char h, char m, char s);

