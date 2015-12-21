/*

    Kernel routines
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/


/* interrupts                                       */

#define KERN_IVEC       0x0000
#define KERN_IRQ_UART0  0x02
#define KERN_IRQ_UART1  0x03
#define KERN_IRQ_IDE    0x04
#define KERN_IRQ_RTC    0x07

/* MSW flags                                        */

#define KERN_MSW_OR     0x01
#define KERN_MSW_AND    0x00
#define KERN_MSW_STI    0xef /* 0b11101111 */
#define KERN_MSW_CLI    0x10 /* 0b00010000 */
#define KERN_MSW_ENS    0xdf /* 0b11011111 */
#define KERN_MSW_DIS    0x20 /* 0b00100000 */

/* Memory bank registers                            */

#define KERN_REG_SUPER_CODEPAGE0 0x2000
#define KERN_REG_SUPER_CODEPAGE1 0x2200
#define KERN_REG_SUPER_DATAPAGE0 0x2400
#define KERN_REG_SUPER_DATAPAGE1 0x2600
#define KERN_REG_USER_CODEPAGE0  0x2800
#define KERN_REG_USER_CODEPAGE1  0x2a00
#define KERN_REG_USER_DATAPAGE0  0x2c00
#define KERN_REG_USER_DATAPAGE1  0x2e00

/* ASCII characters                                 */

#define KERN_ASCII_RETURN 0x0d
#define KERN_ASCII_SPACE  0x20
#define KERN_ASCII_TAB    0x09
#define KERN_ASCII_DEL    0x7f

extern void             __kern_mswflg(unsigned char __mode, unsigned char __mask);
extern unsigned char    __kern_mswld(void);
extern void             __kern_mswst(unsigned char __msw);
extern void             __kern_isrvec(unsigned char __intno, void (*__israddr)(void));
extern void             __kern_mempageset(unsigned int __pagereg, unsigned char __pageno);

