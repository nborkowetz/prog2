/* ex_wait_inf  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    int i = 0;

    pid=fork();

    if(pid < 0){
        return -1;
    }
    else if(pid == 0){
        while(1){
            printf("Sono il processo figlio: %d\n",++i);
            sleep(1);
        }
    }
    else{
        /* wait(&status); */
        sleep(8);
        printf("Sono il processo padre e sto terminando!\n");
        exit(0);
    }
}
