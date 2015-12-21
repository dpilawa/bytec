/*

    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

#include "kernel.h"
#include "rs232.h"
#include "klibc.h"
#include "shell.h"
#include "rtc.h"
#include "mm.h"
#include "pmem.h"

char memory[16 * 1024];

int main(void)
{
    /* initialize kernel memory manager                         */
    __kern_mm_init(memory, 16 * 1024);
    
    /* initialize UARTs                                         */
    __kern_rs232_init(KERN_UART_UART0, KERN_UART_LCR_BAUD9K6);
    __kern_isrvec(KERN_IRQ_UART0, __kern_rs232_uart0isr);

    __kern_rs232_init(KERN_UART_UART1, KERN_UART_LCR_BAUD9K6);
    __kern_isrvec(KERN_IRQ_UART1, __kern_rs232_uart1isr);

    /* enable interrupts                                        */
    __kern_mswflg(KERN_MSW_AND, KERN_MSW_STI);    

    /* print UARTs messages                                     */
    __kern_rs232_statusmsg(KERN_UART_UART0);
    __kern_rs232_statusmsg(KERN_UART_UART1);

    /* detect and initialize real time clock                    */
    __kern_rtc_init();

    /* detect physical memory and initialize pages table        */ 
    __kern_pmem_init();

    /* print welcome message                                    */
    kprintf("\nBYTEC/16 Homebrew Computer Monitor/OS\n");
    kprintf("Dawid Pilawa (C) 2009-2015\n\n");

    /* run shell                                                */
    __kern_shell();
    
    return 0;    
}
