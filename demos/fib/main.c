
unsigned char *tty = (unsigned char*)0x1000;

void serial_init() {
	*(tty+3) = 0x80;
	*(tty)   = 0x0c;
	*(tty+1) = 0;
	*(tty+3) = 0x03;
	*(tty+2) = 0x07;
	*(tty+1) = 0;
}

void serial_putc(char c) {
	*(tty) = c;

	/* wait for LSR5 bit to be set */
	while ((*(tty+5) & 0x20)==0);
}

void serial_print_str(const char *s) {
	
	char c;
	
	while(c = *s++) {
		serial_putc(c);
	}
}

void serial_print_num(unsigned int n) {
	
	unsigned int divisors[] = {10000,1000,100,10};
	char digits[] = "0123456789";
	char digit;
	int d;
	int tz=1;
		
	for (d=0; d<=3; d++) {
		digit=0;
		while (n-divisors[d]<n) {
			n-=divisors[d];
			digit++;
			tz=0;
		}
		if (!tz) serial_putc(digits[digit]);
	}
	serial_putc(digits[n]);
}

int fib(int n) {
	if (n < 2) {
		return n;
	} else {
		return (fib(n-1) + fib(n-2));
	}
}

void main() {

	int i,j;

	serial_init();
	
    for (j=1; 1; j++) {
        serial_print_str("run#");
        serial_print_num(j);
        serial_putc(0x1b);
        serial_putc('E');
    	for (i=1; i<=20; i++) {
	    	serial_print_str("f(");
		    serial_print_num(i);
		    serial_print_str(")=");
		    serial_print_num(fib(i));
		    serial_putc(0x1b);
		    serial_putc('E');    
	    }
    }
	
}

