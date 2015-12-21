/*

    Elements of "standard" C library
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

#include "mm.h"
#include "kernel.h"
#include "rs232.h"
#include "klibc.h"
#include "stdarg.h"

/* globals                                                              */

unsigned int stdout_uart = KERN_UART_UART0;
unsigned int io_uart = KERN_UART_UART1;

/* put one character to the output                                      */
void kputc(char c)
{
    __kern_rs232_putc(stdout_uart, c);
}

/* get one character from input                                         */
char kgetc(void)
{
    return __kern_rs232_getc(stdout_uart);
}

/* print zero terminated string                                         */
void kpstr(const char *s) 
{
    const char *s_ptr = s;
    unsigned char c;

    /* proceed until zero                                               */
    while (c=*s_ptr++)
    {
        kputc(c);
    }
}

/* get RETURN terminated string from input
   and store zero terminated string at a given pointer                  */
void kgstr(char *s) 
{
    char *s_ptr = s;
    unsigned char c;

    /* proceed until RETURN                                             */
    while ((c = kgetc()) != KERN_ASCII_RETURN)
    {
        /* store and echo character                                     */
        if (c != KERN_ASCII_DEL)
        {
            /* store character and advance pointer                      */
            *s_ptr++=c;
            /* echo                                                     */
            kputc(c);
        }
        /* handle DEL character in a special way                        */
        else if (s_ptr != s)
        {
            /* decrease pointer (eat one character)                     */
            s_ptr--;
            /* echo DEL                                                 */
            kputc(c);
        }
    }

    /* terminate string with zero                                       */
    *s_ptr = 0;

    /* echo newline                                                     */
    kputc('\n');
}

/* print decimal number to output                                       */
void kpnum(int n, int is_signed, unsigned int len, char pad) 
{
    unsigned int divisors[] = {1,10,100,1000,10000};
    char digits[] = "0123456789";
    unsigned int digit;
    int num = n;
    int d;
    int lz = 1;
    
    /* check integer sign                                               */
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

    /* print number                                                     */
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

/* print decimal number to output                                       */
void kphex(int n, unsigned int len, char pad)
{
    char hex[] = "0123456789abcdef";
    int d;
    int nibble;
    int lz = 1;
    int slen;

    slen = len < 3 ? 3 : len;

    /* print number                                                     */
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


/* print formatted string to the output                                 */
void kprintf(char *fmt, ...)
{
    va_list ap;
    char *p;
    char *sval;
    int ival;
    char pad = 0x20; /* space */
    int len = 0;
    int i;

    va_start(ap, fmt);

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
                ival = va_arg(ap, int);
                /* print signed decimal number                          */
                kpnum(ival, 1, len, pad);
                break;
            case 'u':
                ival = va_arg(ap, int);
                /* print unsigned decimal number                        */
                kpnum(ival, 0, len, pad);
                break;
            case 'x':
                ival = va_arg(ap, int);
                /* print hex number                                     */
                kphex(ival, len, pad);
                break;
            case 's':
                sval = va_arg(ap, char *);
                /* prints plain string                                  */
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

    va_end(ap);
}

/* check if character is whitespace                                     */
int is_white(char c)
{
    return (c==KERN_ASCII_SPACE ||
            c==KERN_ASCII_TAB);
}

/* check if character is a digit                                        */
int is_digit(char c)
{
    return ((c>='0' && c<='9') ? 1 : 0);
}

/* scan formatted input - inner loop                                    */
char* scan(va_list ap, const char *str, char *fmt)
{
    char *sval;
    int *ival;
    int isgn;

    for (;*fmt;fmt++)
    {

        /* strip whitespace from formatting string                      */
        if (is_white(*fmt)) 
        {
            continue;
        }

        /* strip whitespace from input                                  */
        while (is_white(*str))
        {
            str++;
        }

        /* exit if input buffer ended                                   */
        if (*str=='\0')
        {
            return fmt;
        }

        /* scan non formatting string until whitespace or end of string */
        if (*fmt != '%')
        {
            if (*fmt==*str++)
            {
                continue;
            }
            else
            {
                /* the strings did not match                            */
                return (char*)0;
            }

        }
        
        /* scan into variable                                           */
        switch (*++fmt)
        {
            case 's':
                sval = va_arg(ap, char *);
                while (!is_white(*str) && *str!='\0')
                {
                    *sval++ = *str++;
                }
                *sval = '\0';
                break;
            case 'u':
            case 'd':
                ival = va_arg(ap, int *);
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

/* scan formatted input                                                 */
int kscanf(char *fmt, ...)
{
    va_list ap;
    char str[256];

    va_start(ap, fmt);
    do 
    {
        kgstr(str);
        fmt = scan(ap, str, fmt);
        if (!fmt)
            break;
    }
    while (*fmt!='\0');
    va_end(ap);

    if (!fmt)
        return 0;
    else
        return 1;

}

/* scan formatted string                                                */
int ksscanf(char *str, char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fmt = scan(ap, str, fmt);
    va_end(ap);

    /* check if error detected during scan                              */
    if (!fmt)
        return 0;

    /* check if end of formatting string was reached                    */
    if (*fmt=='\0')
        return 1;
    else
        return 0;  

}

/* compare two strings                                                  */
int kstrcmp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2; s1++, s2++)
        if (*s1 == '\0')
            return 0;

    return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}

/* check string length                                                  */
int kstrlen(const char *str)
{
    const char *s;

    for (s = str; *s; ++s);
    return (int)(s - str);
}

/* read binary data                                                     */
void kread(char *ptr, unsigned int size, unsigned int nmemb)
{
    __kern_rs232_read(io_uart, (unsigned char *)ptr, size, nmemb);
}

/* write binary data                                                    */
void kwrite(const char *ptr, unsigned int size, unsigned int nmemb)
{
    __kern_rs232_write(io_uart, (unsigned char*)ptr, size, nmemb);
}

/* allocate memory block                                                */
char* kmalloc(unsigned int size)
{
    return __kern_mm_alloc(size);
}

/* free memory block                                                    */
int kfree(char *ptr)
{
    return __kern_mm_free(ptr);
}

