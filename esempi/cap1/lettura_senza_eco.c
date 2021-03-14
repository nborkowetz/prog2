/* lettura senza eco */

#include <termios.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int lettura_caratteri(char *buff, unsigned size)
{
    int n;
    struct termios attr;  /* usata per leggere e modificare */
                          /* attributi del terminale*/

    write(STDOUT_FILENO, "Battere alcuni caratteri: ", 27);

    if(tcgetattr(STDIN_FILENO, &attr) != 0) 
        return 1;
    attr.c_lflag &= ~(ECHO);
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr) != 0) 
        return 1;
    n = read(STDIN_FILENO, buff, size);
    /* attr.c_lflag |= ECHO;
       if(tcsetattr(STDIN_FILENO, TCSANOW, &attr) != 0) 
           return 1; 
    */
    return(n);
}

int main(int argc, char *argv[]) 
{
    char stringa[100];
    int i;

    i=lettura_caratteri(stringa, 10);
    if (i >= 0) {
        printf("\n");
        printf("Numero di caratteri letti: %d\n",i);
    }
}
