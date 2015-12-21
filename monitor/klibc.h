/*

    Elements of standard C library 
    BYTEC/16 Homebuilt Microcomputer Monitor Program
    Dawid Pilawa (C) 2015

*/

extern void kputc(char c);
extern char kgetc(void);
extern void kpstr(const char *s);
extern void kgstr(char *s);

extern void kprintf(char *fmt, ...);
extern int  kscanf (char *fmt, ...);
extern int  ksscanf(char *str, char *fmt, ...);
extern int  kstrcmp(const char *s1, const char *s2);
extern int  kstrlen(const char *str);

extern void kread(char *ptr, unsigned int size, unsigned int nmemb);
extern void kwrite(const char *ptr, unsigned int size, unsigned int nmemb);

extern char* kmalloc(unsigned int size);
extern int   kfree(char* ptr);
