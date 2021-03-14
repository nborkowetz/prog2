//test push 

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


char *findExitPattern(char string[]){
    const char PATTERN[] = "exit";
    
    return strstr(string, PATTERN);
} 

int main(int argc, char *argv[]){
    struct termios attr0;

    char dev0[20], dev1[20], buffer[100];
    int descriptor[2], buffer_size = 100;


    // terminale per la scrittura dei comandi 
    printf("insert first device: ");  //sostituire con IO POSIX
    scanf("%s", dev0);
    descriptor[0] = open(dev0, O_RDONLY);

    if(descriptor[0] < 0){
        printf("error \n");
        exit(EXIT_FAILURE);
    }

    // terminale per la visulalizzazione dei comandi 
    printf("insert second device: ");  //sostituire con IO POSIX
    scanf("%s", dev1);
    descriptor[1] = open(dev1, O_RDWR);

    if(descriptor[1] < 0){
        printf("error \n");
        exit(EXIT_FAILURE);
    }

    if(tcgetattr(descriptor[0], &attr0) == 0){
        attr0.c_lflag |= ICANON;
        if(tcsetattr(descriptor[0], TCSADRAIN, &attr0) != 0){
            printf("error \n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("error \n");
        exit(EXIT_FAILURE);
    }

    while(1){
        int bytes_read = 0;
        
        bytes_read = read(descriptor[0], &buffer, buffer_size);
        if(bytes_read > 0){
            if(findExitPattern(buffer) == NULL){
                printf ("read %d byte from %s \n", bytes_read, dev0);
                write(descriptor[1], &buffer, bytes_read);
                printf ("wrote %d byte on %s \n", bytes_read, dev1);
            } else {
                printf("Exiting... \n");
                exit(EXIT_SUCCESS);
            }
        }

        sleep(1); 
    }
}