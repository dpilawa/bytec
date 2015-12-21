/*

    RS232 driver
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

/* UART addresses */
#define KERN_UART_UART0 0x1000
#define KERN_UART_UART1 0x1010

/* UART registers */
#define KERN_UART_RBR 0x00        /* Receiver Buffer Register (DLAB=0)       */
#define KERN_UART_THR 0x00        /* Tramsmitter Holding Register (DLAB=0)   */
#define KERN_UART_DLL 0x00        /* Divisor Latch LS (DLAB=1)               */
#define KERN_UART_DLM 0x01        /* Divisor Latch MS (DLAB=1)               */
#define KERN_UART_IER 0x01        /* Interrupt Enable Register (DLAB=0)      */
#define KERN_UART_IIR 0x02        /* Interrupt Identification Register       */
#define KERN_UART_FCR 0x02        /* FIFO Control Register                   */
#define KERN_UART_LCR 0x03        /* Line Control Register                   */
#define KERN_UART_MCR 0x04        /* Modem Control Register                  */
#define KERN_UART_LSR 0x05        /* Line Status Register                    */
#define KERN_UART_MSR 0x06        /* Modem Status Register                   */
#define KERN_UART_SCR 0x07        /* Scratch Register                        */

/* Line Control Register flags                                               */
#define KERN_UART_LCR_8N1    0x03 /* 0b00000011 8 bits, no parity, 1 stop    */
#define KERN_UART_LCR_DLAB1  0x80 /* 0b10000000 set DLAB to 1                */
#define KERN_UART_LCR_DLAB0  0x00 /* set DLAB to 0                           */

/* FIFO Control Register flags                                               */
#define KERN_UART_FCR_FIEN   0x01 /* 0b00000001 enable FIFOs (XMIT & RCVR)   */
#define KERN_UART_FCR_CLRB   0x06 /* 0b00000110 clear all FIFO buffers       */
#define KERN_UART_FCR_TRGR14 0xc0 /* 0b11000000 FIFO trigger level 14 bytes  */
#define KERN_UART_FCR_TRGR08 0x80 /* 0b10000000 FIFO trigger level 8 bytes   */
#define KERN_UART_FCR_TRGR04 0x40 /* 0b01000000 FIFO trigger level 4 bytes   */
#define KERN_UART_FCR_TRGR01 0x00 /* 0b00000000 FIFO trigger level 1 byte    */

/* Modem Control Register flags                                              */
#define KERN_UART_MCR_RTS    0x02 /* 0b00000010 set /RTS                     */

/* Modem Status Register flags                                               */
#define KERN_UART_MSR_CTS    0x10 /* 0b00010000 modem /CTS                   */

/* Line Status Register flags                                                */
#define KERN_UART_LSR_THRE   0x20 /* 0b00100000 line THRE                    */

/* Interrupt Enable flags                                                    */
#define KERN_UART_IER_RDA    0x01 /* 0b0001 received data available          */
#define KERN_UART_IER_THRE   0x02 /* 0b0010 transmitter holding reg empty    */
#define KERN_UART_IER_RLS    0x04 /* 0b0100 receiver line status             */
#define KERN_UART_IER_MS     0x08 /* 0b1000 modem status                     */

/* Baud Rate                                                                 */
#define KERN_UART_LCR_BAUD56K    0x02
#define KERN_UART_LCR_BAUD38K4   0x03
#define KERN_UART_LCR_BAUD19K2   0x06
#define KERN_UART_LCR_BAUD9K6    0x0c

/* Buffer Status Flags                                                       */
#define KERN_UART_BUF_EMPTY      0x00     
#define KERN_UART_BUF_NEMPTY     0x01                                        
#define KERN_UART_BUF_FULL       0xff

/* cyclic receive/transfer buffer                                            */
typedef struct {
    unsigned char buf[256];
    unsigned char rptr;
    unsigned char wptr;
    unsigned char fflg;
} uartbuf_t;

/* externs                                                                   */
extern void __kern_rs232_uart0isr(void);
extern void __kern_rs232_uart1isr(void);
extern void __kern_rs232_init(unsigned int __uartreg, unsigned char __baudrate);
extern void __kern_rs232_statusmsg(unsigned int __uartreg);
extern void __kern_rs232_putc(unsigned int __uartreg, char __c);
extern unsigned char __kern_rs232_getc(unsigned int __uartreg);
extern void __kern_rs232_write(unsigned int __uartreg, unsigned char *__ptr,
                            unsigned int __size, unsigned int __nblk);
extern void __kern_rs232_read(unsigned int __uartreg, unsigned char *__ptr,
                            unsigned int __size, unsigned int __nblk);

