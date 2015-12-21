/*

    RS232 driver
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

#include "kernel.h"
#include "rs232.h"
#include "klibc.h"

#define MAGIC1 0x3f
#define MAGIC2 0x71

/* globals                                                              */

uartbuf_t __kern_rs232_uart0rbuf;
uartbuf_t __kern_rs232_uart0tbuf;
uartbuf_t __kern_rs232_uart1rbuf;
uartbuf_t __kern_rs232_uart1tbuf;
int uart0_present = 0;
int uart1_present = 0;
int uart0_16550a = 0;
int uart1_16550a = 0;
unsigned int uart0_baudrate;
unsigned int uart1_baudrate;

/* initialize serial line for 8n1 with selected baud rate               */
void __kern_rs232_init(unsigned int __uartreg, unsigned char __baudrate) 
{
    unsigned char *uart = (unsigned char*)__uartreg;
    uartbuf_t *rbuf,*tbuf;
    unsigned char b;

    /* check if UART present by probing scratch register twice          */
    *(uart+KERN_UART_SCR) = MAGIC1;
    if ((b = *(uart+KERN_UART_SCR)) != MAGIC1)
        return;

    *(uart+KERN_UART_SCR) = MAGIC2;
    if ((b = *(uart+KERN_UART_SCR)) != MAGIC2)
        return;

    if (__uartreg==KERN_UART_UART0)
    {
        uart0_present = 1;
        uart0_baudrate = __baudrate;
    }
    else
    {
        uart1_present = 1;
        uart1_baudrate = __baudrate;
    }

    /* set buffer bounds                                                */
    rbuf = (__uartreg==KERN_UART_UART0) ? &__kern_rs232_uart0rbuf : &__kern_rs232_uart1rbuf;
    tbuf = (__uartreg==KERN_UART_UART0) ? &__kern_rs232_uart0tbuf : &__kern_rs232_uart1tbuf;
    rbuf->wptr = rbuf->rptr = rbuf->fflg = 0;
    tbuf->wptr = tbuf->rptr = tbuf->fflg = 0; 

    /* set baud rate and serial line parameters                         */
    *(uart+KERN_UART_LCR) = KERN_UART_LCR_DLAB1;
    *(uart+KERN_UART_DLL) = __baudrate;
    *(uart+KERN_UART_DLM) = 0x00;
    *(uart+KERN_UART_LCR) = KERN_UART_LCR_DLAB0|KERN_UART_LCR_8N1;
    
    /* enable FIFO and clear XMIT and RCVR buffers                      */
    *(uart+KERN_UART_FCR) = KERN_UART_FCR_FIEN|KERN_UART_FCR_CLRB|KERN_UART_FCR_TRGR14;
 
    /* determine if 16550 or 16550A                                     */
    if (*(uart+KERN_UART_IIR)&0xc0 == 0xc0)
    {
        if (__uartreg==KERN_UART_UART0)
            uart0_16550a = 1;
        else
            uart1_16550a = 1;
    }

    /* enable UART interrupts                                           */
    *(uart+KERN_UART_IER) = KERN_UART_IER_RDA|KERN_UART_IER_MS;

    /* notify peer that we are ready to accept characters               */
    *(uart+KERN_UART_MCR) = KERN_UART_MCR_RTS;
}

/* print UARTs status information                                       */
void __kern_rs232_statusmsg(unsigned int __uartreg)
{
    int uart_present;
    int uart_16550a;
    unsigned char uart_baudrate;
    unsigned char *uart = (unsigned char*)__uartreg;

    switch (__uartreg)
    {
        case KERN_UART_UART0:
            kprintf("UART0: ");
            uart_present = uart0_present;
            uart_baudrate = uart0_baudrate;
            uart_16550a = uart0_16550a;
            break;
        case KERN_UART_UART1:
            kprintf("UART1: ");
            uart_present = uart1_present;
            uart_baudrate = uart1_baudrate;
            uart_16550a = uart1_16550a;
            break;
    }

    if (uart_present)
    {
        kprintf("found ");
        if (uart_16550a)
            kprintf("16550A ");
        else 
            kprintf("16550 ");
        kprintf("at 0x%04x (", __uartreg);
    }
    else
    {
        kprintf("not found\n");
        return;
    }

    switch (uart_baudrate)
    {
        case KERN_UART_LCR_BAUD56K:
            kprintf("56000");
            break;
        case KERN_UART_LCR_BAUD38K4:
            kprintf("38400");
            break;
        case KERN_UART_LCR_BAUD19K2:
            kprintf("19200");
            break;
        case KERN_UART_LCR_BAUD9K6:
            kprintf("9600");
            break;
        default:
            kprintf("nonstandard");
    }
    kprintf(" bps)\n");
}

/* get one character from a serial port                                 */
unsigned char __kern_rs232_getc(unsigned int __uartreg) 
{
    unsigned char   *uart = (unsigned char*)__uartreg;
    unsigned char   msw;
    unsigned char   c;
    uartbuf_t       *rbuf;
    rbuf = (__uartreg==KERN_UART_UART0) ? &__kern_rs232_uart0rbuf : &__kern_rs232_uart1rbuf;

    /* since we are changing the MSW EI flags, MSW needs to be stored in
       temp variable to be restored upon getc completion                */ 
    msw = __kern_mswld();

    /* we are entering ctitical region so interrupts should be disabled */
    __kern_mswflg(KERN_MSW_OR, KERN_MSW_CLI);

    /* if buffer is empty, wait until characted arrives by momentarily
       enabling the interrupts                                          */
    while (rbuf->fflg==KERN_UART_BUF_EMPTY)
    {
        __kern_mswflg(KERN_MSW_AND, KERN_MSW_STI);
        __kern_mswflg(KERN_MSW_OR, KERN_MSW_CLI);
    }
    
    /* read from buffer                                                 */
    /* read character from buffer and advance read pointer              */
    c = rbuf->buf[rbuf->rptr++];
    if (rbuf->rptr==rbuf->wptr)
    /* buffer empty                                                     */
    {
        rbuf->fflg=KERN_UART_BUF_EMPTY;
    }
    else
    /* buffer non-empty                                                 */
    {
        rbuf->fflg=KERN_UART_BUF_NEMPTY;
    }

    /* restore MSW (end critical section)                               */   
    __kern_mswst(msw);

    /* return character                                                 */
    return c;
}

/* send one character to a serial port                                  */
void __kern_rs232_putc(unsigned int __uartreg, char __c) 
{
    unsigned char   *uart = (unsigned char*)__uartreg;
    unsigned char   msw;
    uartbuf_t       *tbuf;
    tbuf = (__uartreg==KERN_UART_UART0) ? &__kern_rs232_uart0tbuf : &__kern_rs232_uart1tbuf;

    /* since we are changing the MSW EI flags, MSW needs to be stored in
       temp variable to be restored upon putc completion                */ 
    msw = __kern_mswld();

    /* we are entering ctitical region so interrupts should be disabled */
    __kern_mswflg(KERN_MSW_OR, KERN_MSW_CLI);

    /* if buffer is full, wait until it is freed by momentarily
       enabling the interrupts                                          */
    while (tbuf->fflg==KERN_UART_BUF_FULL)
    {
        __kern_mswflg(KERN_MSW_AND, KERN_MSW_STI);
        __kern_mswflg(KERN_MSW_OR, KERN_MSW_CLI);
    }

    /* check if buffer is empty and peer allows to send (CTS)
       write directly to UART FIFO if so else write to buffer           */
    if (tbuf->fflg==KERN_UART_BUF_EMPTY
    && (*(uart+KERN_UART_MSR) & KERN_UART_MSR_CTS))
    {
        /* write to FIFO                                                */
        /* wait until FIFO is ready to accept a character (THRE)        */
        while (!(*(uart+KERN_UART_LSR) & KERN_UART_LSR_THRE));
        /* transmit                                                     */
        *(uart+KERN_UART_THR) = __c;
    }
    else 
    {
        /* write to buffer                                              */
        /* write character to buffer and advance write pointer          */
        tbuf->buf[tbuf->wptr++]=__c;
        if (tbuf->wptr==tbuf->rptr)
        /* buffer full                                                  */
        {
            tbuf->fflg=KERN_UART_BUF_FULL;
        }
        else
        /* buffer non-empty                                             */
        {
            tbuf->fflg=KERN_UART_BUF_NEMPTY;
        }
    }

    /* restore MSW (end critical section)                               */   
    __kern_mswst(msw);
}

/* write data to a serial port                                          */
void __kern_rs232_write(unsigned int __uartreg, unsigned char *__ptr, 
                        unsigned int __size, unsigned int __nblk)
{
    unsigned int s, n;

    for (n=0; n < __nblk; n++)
    {
        for (s=0; s < __size; s++)
        {
            __kern_rs232_putc(__uartreg, *__ptr++);
        }
    }
}

/* read data from a serial port                                         */
void __kern_rs232_read(unsigned int __uartreg, unsigned char *__ptr, 
                       unsigned int __size, unsigned int __nblk)
{
    unsigned int s, n;

    for (n=0; n < __nblk; n++)
    {
        for (s=0; s < __size; s++)
        {
            *__ptr++ = __kern_rs232_getc(__uartreg);
        }
    }
}

