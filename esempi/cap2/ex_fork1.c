/* ex_fork1 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    pid_t pid;
    int status;

    printf("Esempio con fork\n");
    pid = fork();

    if(pid < 0){
        printf("Errore in fork!\n");
        return -1;
    }
    else if(pid == 0){
        sleep(20);
        printf("Figlio: Sono il processo figlio\n");
        printf("Figlio: Il pid ricevuto da fork vale %d\n", (int)pid);
        printf("Figlio: Il mio PID vale %d\n", (int)getpid());
        printf("Figlio: Il PID di chi mi ha creato vale %d\n", (int)getppid());
        exit(9);
    }
    else{
        sleep(20);
        printf("Padre: Sono il processo padre\n");
        printf("Padre: Ho creato un figlio con pid %d\n", (int)pid);
        printf("Padre: Il mio PID vale %d\n", (int)getpid());
        printf("Padre: Il PID di chi mi ha creato vale %d\n", (int)getppid());

        wait(&status);
        printf("Padre: valore ritornato dal figlio = %d\n", WEXITSTATUS(status));

        /*WEXITSTATUS(variabilile_di_stato): macro che ritorna il valore a 
                                             8bit ritornato dal processo figlio. */
    }
}
