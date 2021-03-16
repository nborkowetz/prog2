/* ex_execv2_const */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int status;
    char *const vector[] = {"xterm", NULL};
    
    pid = fork();

    if(pid < 0){
        return -1;
    }
    else if(pid == 0){
        printf("Figlio creato e si rigenera in xterm\n");

        status = execv("/usr/bin/xterm", vector);
        if(status == -1){
            printf("\n\nErrore %d in exec!!\n", errno);
        }
    }
    else{
        wait(&status);
        printf("\nIl figlio ha terminato l'esecuzione\n");
    }
}
