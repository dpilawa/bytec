#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>

int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
   /* new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;*/
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

int main()
{
    int key;

    /* initialize the random number generator */
    srand(time(NULL));

    for (;;) {
        key = getkey();
        /* terminate loop on ESC (0x1B) or Ctrl-D (0x04) on STDIN */
        if (key == 0x1B || key == 0x04) {
            break;
        }
        else {
            /* print random ASCII character between 0x20 - 0x7F */
            /*key = (rand() % 0x7F);*/
            printf("%c", ((key < 0x20) ? (key + 0x20) : key));
        }
    }

    return 0;
}
