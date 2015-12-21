#line 1 "klibc.c"

#line 8 "klibc.c"

#line 1 "./mm.h"

#line 9 "./mm.h"








#line 20 "./mm.h"




enum {MM_LEFT, MM_RIGHT, MM_ROOT};


typedef struct memblk {
    unsigned int size;
    unsigned int allocated:1;
    unsigned int leaf:1;
    unsigned int lrr:2;
} memblk_t;


extern memblk_t* __kern_mm_pool;


extern void  __kern_mm_init(char *__pool, unsigned int __size);
extern char* __kern_mm_alloc(unsigned int __size);
extern int   __kern_mm_free(char *__ptr);
extern void  __kern_mm_print_memblk(memblk_t *__blk, unsigned int __depth);

#line 10 "klibc.c"
#line 1 "./kernel.h"

#line 8 "./kernel.h"





































extern void             __kern_mswflg(unsigned char __mode, unsigned char __mask);
extern unsigned char    __kern_mswld(void);
extern void             __kern_mswst(unsigned char __msw);
extern void             __kern_isrvec(unsigned char __intno, void (*__israddr)(void));
extern void             __kern_mempageset(unsigned int __pagereg, unsigned char __pageno);

#line 11 "klibc.c"
#line 1 "./rs232.h"

#line 8 "./rs232.h"



























































typedef struct {
    unsigned char buf[256];
    unsigned char rptr;
    unsigned char wptr;
    unsigned char fflg;
} uartbuf_t;


extern void __kern_rs232_uart0isr(void);
extern void __kern_rs232_uart1isr(void);
extern void __kern_rs232_init(unsigned int __uartreg, unsigned char __baudrate);
extern void __kern_rs232_putc(unsigned int __uartreg, char __c);
extern unsigned char __kern_rs232_getc(unsigned int __uartreg);
extern void __kern_rs232_write(unsigned int __uartreg, unsigned char *__ptr,
                            unsigned int __size, unsigned int __nblk);
extern void __kern_rs232_read(unsigned int __uartreg, unsigned char *__ptr,
                            unsigned int __size, unsigned int __nblk);

#line 12 "klibc.c"
#line 1 "./klibc.h"

#line 8 "./klibc.h"

extern void kputc(char c);
extern char kgetc(void);
extern void kpstr(const char *s);
extern void kgstr(char *s);

extern void kprintf(char *fmt, ...);
extern int  kscanf (char *fmt, ...);
extern int  ksscanf(char *str, char *fmt, ...);
extern int  kstrcmp(const char *s1, const char *s2);
extern int  kstrlen(const char *str);

extern char* kmalloc(unsigned int size);
extern int   kfree(char* ptr);
#line 13 "klibc.c"
#line 1 "./stdarg.h"

#line 20 "./stdarg.h"











#line 33 "./stdarg.h"


#line 36 "./stdarg.h"





#line 42 "./stdarg.h"


#line 46 "./stdarg.h"






#line 54 "./stdarg.h"





#line 60 "./stdarg.h"


#line 63 "./stdarg.h"






#line 71 "./stdarg.h"






typedef char *va_list;





#line 85 "./stdarg.h"






#line 14 "klibc.c"



unsigned int g_uart = 0x1000;


void kputc(char c)
{
    __kern_rs232_putc(g_uart, c);
}


char kgetc(void)
{
    return __kern_rs232_getc(g_uart);
}


void kpstr(const char *s)
{
    const char *s_ptr = s;
    unsigned char c;


    while (c=*s_ptr++)
    {
        kputc(c);
    }
}


#line 46 "klibc.c"
void kgstr(char *s)
{
    char *s_ptr = s;
    unsigned char c;


    while ((c = kgetc()) != 0x0d)
    {

        if (c != 0x7f)
        {

            *s_ptr++=c;

            kputc(c);
        }

        else if (s_ptr != s)
        {

            s_ptr--;

            kputc(c);
        }
    }


    *s_ptr = 0;


    kputc('\n');
}


void kpnum(int n, int is_signed, unsigned int len, char pad)
{
    unsigned int divisors[] = {1,10,100,1000,10000};
    char digits[] = "0123456789";
    unsigned int digit;
    int num = n;
    int d;
    int lz = 1;


    if (is_signed && num < 0)
    {
        kputc('-');
        num = num & 0x7fffU;
        num = 0x8000U-num;
    }

    for (d=len; d>5; d--)
    {
        kputc(pad);
        lz = 0;
    }


    for (d=4; d>=0; d--)
    {
        digit = num / divisors[d];
        if (digit) lz = 0;
        if (lz && d)
        {
            if (d<len) kputc(pad);
        }
        else
        {
            kputc(digits[digit]);
        }
        num = num % divisors[d];
    }
}


void kphex(int n, unsigned int len, char pad)
{
    char hex[] = "0123456789abcdef";
    int d;
    int nibble;
    int lz = 1;
    int slen;

    slen = len < 3 ? 3 : len;


    for (d=slen; d>=0; d--)
    {
        nibble = (n >> (d << 2)) & 0x000fU;
        if (nibble) lz = 0;
        if (lz && d)
        {
            if (d<len) kputc(pad);
        }
        else
        {
            kputc(hex[nibble]);
        }
    }

}



void kprintf(char *fmt, ...)
{
    va_list ap;
    char *p;
    char *sval;
    int ival;
    char pad = 0x20;
    int len = 0;
    int i;

((ap) = (va_list)& fmt +((sizeof(fmt)+sizeof(int)-1) & ~(sizeof(int) -1)));

    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            kputc(*p);
            continue;
        }

        switch (*++p)
        {
            case '0':
                pad = '0';
                break;
            default:
                p--;
                break;
        }

        p++;
        if (*p>='1' && *p<='9')
        {
            len = *p - '0';
        }
        else
        {
            p--;
        }

        switch (*++p)
        {
            case 'd':
                ival =(*((int *)((va_list)((ap) = (void *)((va_list)(ap) +((sizeof(int)+sizeof(int)-1) & ~(sizeof(int) -1)))) -((sizeof(int)+sizeof(int)-1) & ~(sizeof(int) -1)))));

                kpnum(ival, 1, len, pad);
                break;
            case 'u':
                ival =(*((int *)((va_list)((ap) = (void *)((va_list)(ap) +((sizeof(int)+sizeof(int)-1) & ~(sizeof(int) -1)))) -((sizeof(int)+sizeof(int)-1) & ~(sizeof(int) -1)))));

                kpnum(ival, 0, len, pad);
                break;
            case 'x':
                ival =(*((int *)((va_list)((ap) = (void *)((va_list)(ap) +((sizeof(int)+sizeof(int)-1) & ~(sizeof(int) -1)))) -((sizeof(int)+sizeof(int)-1) & ~(sizeof(int) -1)))));

                kphex(ival, len, pad);
                break;
            case 's':
                sval =(*((char * *)((va_list)((ap) = (void *)((va_list)(ap) +((sizeof(char *)+sizeof(int)-1) & ~(sizeof(int) -1)))) -((sizeof(char *)+sizeof(int)-1) & ~(sizeof(int) -1)))));

                if (kstrlen(sval)>=len)
                {
                    kpstr(sval);
                }
                else
                {
                    for (i=0;i<=len-kstrlen(sval);i++)
                    {
                        kputc(pad);
                    }
                }
                break;
            default:
                kputc(*p);
                break;
        }

        len = 0;
        pad = 0x20;

    }

;
}


int is_white(char c)
{
    return (c== 0x20 ||
            c== 0x09);
}


int is_digit(char c)
{
    return ((c>='0' && c<='9') ? 1 : 0);
}


char* scan(va_list ap, const char *str, char *fmt)
{
    char *sval;
    int *ival;
    int isgn;

    for (;*fmt;fmt++)
    {


        if (is_white(*fmt))
        {
            continue;
        }


        while (is_white(*str))
        {
            str++;
        }


        if (*str=='\0')
        {
            return fmt;
        }


        if (*fmt != '%')
        {
            if (*fmt==*str++)
            {
                continue;
            }
            else
            {

                return (char*)0;
            }

        }


        switch (*++fmt)
        {
            case 's':
                sval =(*((char * *)((va_list)((ap) = (void *)((va_list)(ap) +((sizeof(char *)+sizeof(int)-1) & ~(sizeof(int) -1)))) -((sizeof(char *)+sizeof(int)-1) & ~(sizeof(int) -1)))));
                while (!is_white(*str) && *str!='\0')
                {
                    *sval++ = *str++;
                }
                *sval = '\0';
                break;
            case 'u':
            case 'd':
                ival =(*((int * *)((va_list)((ap) = (void *)((va_list)(ap) +((sizeof(int *)+sizeof(int)-1) & ~(sizeof(int) -1)))) -((sizeof(int *)+sizeof(int)-1) & ~(sizeof(int) -1)))));
                *ival = 0;
                isgn = 1;
                if (*fmt=='d' && *str=='-')
                {
                    isgn = -1;
                    str++;
                }
                while (is_digit(*str))
                {
                    *ival = *ival * 10;
                    *ival = *ival + (*str-'0');
                    str++;
                }
                *ival=*ival*isgn;
                break;
            default:
                break;
        }

    }

    return fmt;

}


int kscanf(char *fmt, ...)
{
    va_list ap;
    char str[256];

((ap) = (va_list)& fmt +((sizeof(fmt)+sizeof(int)-1) & ~(sizeof(int) -1)));
    do
    {
        kgstr(str);
        fmt = scan(ap, str, fmt);
        if (!fmt)
            break;
    }
    while (*fmt!='\0');
;

    if (!fmt)
        return 0;
    else
        return 1;

}


int ksscanf(char *str, char *fmt, ...)
{
    va_list ap;

((ap) = (va_list)& fmt +((sizeof(fmt)+sizeof(int)-1) & ~(sizeof(int) -1)));
    fmt = scan(ap, str, fmt);
;


    if (!fmt)
        return 0;


    if (*fmt=='\0')
        return 1;
    else
        return 0;

}


int kstrcmp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;

    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}


int kstrlen(const char *str)
{
    const char *s;

    for (s = str; *s; ++s);
    return (int)(s - str);
}


char* kmalloc(unsigned int size)
{
    return __kern_mm_alloc(size);
}


int kfree(char *ptr)
{
    return __kern_mm_free(ptr);
}

