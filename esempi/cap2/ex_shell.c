/* ex_shell */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    char str[40];

    while(1){
        printf("--> ");
        scanf("%s", str);

        pid = fork();

        if(pid < 0){
            return 1;
        }
        else if(pid == 0){
            execlp(str, str, NULL);
        }
        else{
            /* wait(&status); */
        } 
    }
    printf("\n\nDone...\n");
}
