/* lettura non canonica */

#include <termios.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int lettura_non_canonica(char *buff,unsigned size) {
    struct termios attr;	
    int n, ncar, timeout;

    printf("Numero di caratteri da leggere: ");
    scanf("%d", &ncar);
    printf("Timeout in decimi di secondo: ");
    scanf("%d", &timeout);
    printf("Battere i caratteri:");
    fflush(stdout);            

    if(tcgetattr(STDIN_FILENO, &attr) != 0) 
        return (-1);
    attr.c_lflag &= ~(ICANON);
    attr.c_cc[VMIN] = ncar;
    attr.c_cc[VTIME] = timeout;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr) != 0) 
        return 1;
    n = read(STDIN_FILENO, buff, size);
    attr.c_lflag |= ICANON;

    if(tcsetattr(STDIN_FILENO, TCSANOW, &attr) != 0) 
        return 1;

    return(n);
}

int main(int argc, char *argv[]) {
    char stringa[100];
    int i, j;

    i = lettura_non_canonica(stringa, 80);
    if( i >= 0) {
        printf("\nNumero di caratteri letti: %d\n", i);
        printf("Codici caratteri letti:");

        for (j=0; j<i; j++)
            printf(" %d", stringa[j]);

        printf("\n");
    }
}
