#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

int main() {
	
	int ptm;
	char c;
	char c2 = '_';
	struct termios t;
	
	if ((ptm=getpt()) < 0)
	{
		printf("error creating pair\n");
		return -1;
	}
	
	if (grantpt(ptm) < 0 || unlockpt(ptm) < 0)
	{
		printf("error in grant/unlock\n");
		return -1;			
	}
	
	tcgetattr(ptm, &t);
	cfmakeraw(&t);
	tcsetattr(ptm, TCSANOW, &t);
	
	printf("%s\n", ptsname(ptm));
	
	while (read(ptm, &c, 1))
	{
		write(ptm, &c, 1);
		write(ptm, &c2, 1);
	}
	
	close(ptm);
	
}
