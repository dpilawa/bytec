unsigned char *tty = (unsigned char*)0x1000;

void debug_init() 
{
	*(tty+3) = 0x80;
	*(tty)   = 0x0c;
	*(tty+1) = 0;
	*(tty+3) = 0x03;
	*(tty+2) = 0x07;
	*(tty+1) = 0;
}

void debug_putc(char c) 
{
	*(tty) = c;

	/* wait for LSR5 bit to be set */
	while ((*(tty+5) & 0x20)==0);
}

void debug_print_str(const char *s) 
{
	char c;
	
	while(c = *s++) {
		debug_putc(c);
	}
}
