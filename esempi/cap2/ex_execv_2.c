/* ex_execv2 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define V_SIZE 6

int main(int argc, char *argv[])
{
    pid_t pid;
    int i;
    int status;
    char *vector_ptr[V_SIZE];           //Vettore di puntatori a string
    char vector[V_SIZE-1][10];          //Array di stringhe da 10 char (matrice)

    /* Assegnazione degli indirizzi al vettore di puntatori */
    for(i = 0; i < V_SIZE; i++){
        vector_ptr[i] = &vector[i][0];
    }

    /* Definizione del contenuto degli array di stringhe */
    strcpy(vector[0], "xterm");         //Nome del file binario
    strcpy(vector[1], "-bg");           //Opzione per imp. il colore di sfondo
    strcpy(vector[2], "blue");	        //Colore dello sfondo
    strcpy(vector[3], "-fg");           //Opzione per imp. il colore del testo
    strcpy(vector[4], "green");         //Colore del testo
    vector_ptr[V_SIZE-1] = NULL;        //Terminatore del vettore di puntatori

    /* Biforcazione del processo */
    pid = fork();

    if(pid < 0){         //Errore in fork
        return -1;
    }
    else if(pid == 0){   //Processo figlio
        printf("Figlio creato e si rigenera in xterm\n");

        status = execv("/usr/bin/xterm", (char * const *) vector_ptr);
        if(status == -1){
            printf("\n\nErrore %d in exec!!\n", errno);
        }
    }
    else{                //Processo padre
        wait(&status);
        printf("\nIl figlio ha terminato l'esecuzione\n");
    }
}
