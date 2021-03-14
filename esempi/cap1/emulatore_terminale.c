/* emulatore terminale */

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>

int main(int argc, char *argv[]) {
    int ioptr[2], nmax = 80, k0, k1;
    char device0[80], device1[80], stringa[80];
    struct termios attr0, attr1; 

    printf("primo device: ");
    scanf("%s", device0);
    ioptr[0] = open(device0, O_RDONLY | O_NONBLOCK);
    if (ioptr[0] < 0) { 
        printf("Errore nr. %d nell'apertura della linea!\n", errno);
        return 1;
    }

    printf("secondo device: ");
    scanf("%s", device1);
    ioptr[1] = open(device1, O_RDWR);
    if (ioptr[1] < 0) { 
        printf("Errore nr. %d nell'apertura della linea!\n", errno); 
        return 1;
    }

    tcgetattr(ioptr[0],&attr0);
    attr0.c_lflag &= ~(ICANON);
    attr0.c_lflag &= ~(ECHO);
    attr0.c_cc[VMIN] = 1;
    tcsetattr(ioptr[0], TCSADRAIN, &attr0);
    /*
      tcgetattr(ioptr[1], &attr1);
      attr1.c_lflag &= ~(ICANON);
      attr1.c_lflag &= ~(ECHO);
      attr1.c_cc[VMIN] = 1;
      tcsetattr(ioptr[1], TCSADRAIN, &attr1);
    */
    while(1) {
        k0 = read(ioptr[0], stringa, nmax);
        printf("Letto %d caratteri da ioptr[0]\n", k0);
        if(k0 > 0)
            write(ioptr[1], stringa, k0);
        /*
          k1=read(ioptr[1], stringa, nmax);
          printf("Letto %d caratteri da ioptr[1]\n", k1);
          if(k1 > 0)
              write(ioptr[0], stringa, k1);
        */
        sleep(1);
    }
}
