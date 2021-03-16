/* ex_execlp */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;

    pid = fork();

    if(pid < 0){
        printf("Error in fork\n!");
        return 1;
    }
    else if(pid == 0){
        execlp("cal", "cal", "-3", (char *)NULL);
    }
    else{
        wait(&status);
        printf("\n\nDone...\n");
    }
}
