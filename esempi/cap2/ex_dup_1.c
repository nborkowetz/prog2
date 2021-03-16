/* ex_dup_1 */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int fd;
    int retval;

    fd = dup(STDOUT_FILENO);
    if (fd < 0) 
        printf("Errore in dup!\n");
    else
        printf("Duplicato di %d: %d\n",STDOUT_FILENO, fd);

    retval = close(STDOUT_FILENO);
    if (retval < 0) 
        perror("Errore in close!!\n");  //Stampa il messaggio sullo std error!!
    else{
        /* Tenta di scrivere in stdout*/
        retval = printf("Il descriptor 1 stato chiuso\n");
        if (retval <= 0) { 
            perror("Errore di scrittura in printf!\n");
            write(fd, "Scrittura sul canale duplicato\n", 31);
        }
    }
    fd = dup(3);
    printf("Ho rimesso lo stdout in %d\n", fd);
}

