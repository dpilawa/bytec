/* Simplified hostfile for BYTEC/16 */

#include <string.h>

static char rcsid[] = "";

#ifndef LCCDIR
#define LCCDIR "/usr/local/bin/"
#endif

char *suffixes[] = { ".c", ".i", ".s", ".o", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { LCCDIR "cpp",
	"-D__STDC__=1",
	"$1", "$2", "$3", 0 };
char *include[] = { "-I" LCCDIR "include", 0 };
char *com[] = { LCCDIR "rcc", "-target=bytec16",
	"$1", "$2", "$3", 0 };
char *as[] = { "/usr/local/bin/as-b16", "-o", "$3", "$1", "$2", 0 };
char *ld[] = { "/usr/local/bin/ld-b16", "-o", "$3", "$1", "$2"};

extern char *concat(char *, char *);

int option(char *arg) {
	if (strncmp(arg, "-lccdir=", 8) == 0) {
		cpp[0] = concat(&arg[8], "/cpp");
		include[0] = concat("-I", concat(&arg[8], "/include"));
		com[0] = concat(&arg[8], "/rcc");
	}
	else if (strncmp(arg, "-ld=", 4) == 0)
		ld[0] = &arg[4];
	else
		return 0;
	return 1;
}
