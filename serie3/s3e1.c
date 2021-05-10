#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

#define GAME_TIMEOUT 10

void timer_handler(){
    printf("Tempo scaduto !");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    struct sigaction act;

    int number, guess;
    char guess_str[2];

    //set timer_handler as handler for the signal SIGALRM(TIMER)
    //and clear the list of signals to block during 
    //the handler execution
    act.sa_flags = 0;
    act.sa_handler = timer_handler;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);

    //generate a random number between 0 and 99
    srand((int)time(NULL));
    number = rand()%100;
    
    //schedule alarm after 10 seconds
    alarm(GAME_TIMEOUT);

    
    while(1){
        printf("inserisci un numero: ");
        scanf("%d", &guess);

        if(guess == number){
            printf("Hai indovinato, il numero è: %d \n", number);
            exit(EXIT_SUCCESS);
        } else if(guess < number){
            printf("minore\n");
        } else {
            printf("maggiore \n");
        }
    }
}