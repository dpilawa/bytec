/*

    Shell (and several built in functions)
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

#include "klibc.h"
#include "shell.h"
#include "rtc.h"

#define LITTLEENDIAN(x) ((unsigned int)((*(x+1)<<8)+(*(x))))

const char help[] = "\n\
help            - displays this help message\n\
load            - load a program from serial port\n\
run <pid>       - run program in memory\n\
list            - list available programs and free memory\n\
time            - displays current time\n\
time <hh:mm:ss> - sets time\n\
exit            - exits monitor and halts the machine\n";
const char prompt[] = "$ ";
char *cmdstr;
char *cmd;

void __kern_shell_load(void)
{
    char *header;
    unsigned int a_text;
    unsigned int a_data;
    unsigned int a_tbase;
    unsigned int a_dbase;

    /* read a.out header */
    header = kmalloc(88);
    kprintf("Reading header... ");
    kread(header, 88, 1);
    kprintf("done\n");

    /* read code */
    a_text = LITTLEENDIAN(header+8);
    kprintf("Reading %u bytes of code... ", a_text);
    kprintf("done\n");

    /* read data */
    a_data = LITTLEENDIAN(header+16);
    kprintf("Reading %u bytes of code... ", a_data);
    kprintf("done\n");

    /* clean up */
    kfree(header);
}

void __kern_shell_time(char* cstr)
{
    char h, m, s;
    int ih, im, is;

    if (ksscanf(cstr, "time %d:%d:%d", &ih, &im, &is))
    {
        kprintf("Setting clock to %02d:%02d:%02d\n", ih, im, is);
        __kern_rtc_tset((char)ih,(char)im,(char)is);
    }
    else if (ksscanf(cstr, "time"))
    {
        __kern_rtc_tget(&h, &m, &s);
        kprintf("Current time: %02d:%02d:%02d\n", h, m, s);
    }
    else
    {
        kprintf("%s: command syntax error\n", cstr);
    }
}

void __kern_shell(void)
{

    cmdstr = kmalloc(128);
    cmd = kmalloc(32);

    kprintf("Type 'help' then hit RETURN for a list of available commands\n\n");

    for (;;)
    {
        kprintf("%s", prompt);
        kgstr(cmdstr);
        ksscanf(cmdstr, "%s", cmd);

        if (kstrcmp(cmd, "help")==0) 
        {
            kprintf("%s\n", help);
        }
        else if (kstrcmp(cmd, "time")==0) 
        {
            __kern_shell_time(cmdstr);
        }
        else if (kstrcmp(cmd, "load")==0) 
        {
            __kern_shell_load();
        }
        else if (kstrcmp(cmd, "exit")==0) 
        {
            kfree(cmdstr);
            kfree(cmd);
            kprintf("System halted.\n");
            break;
        }
        else 
        {
            kprintf("%s: command not found\n", cmd);
        }

    }

}
