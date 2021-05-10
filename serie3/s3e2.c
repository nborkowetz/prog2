#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

#define TIMER_PERIOD 5

time_t start;

void timer_handler(){
    printf("trascorsi 5 sec \n");
}

void vintr_handler(){
    printf("%ld \n", time(NULL) - start);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
    struct sigaction act[2];

    int number, guess;
    char guess_str[2];

    start = time(NULL);

    //set timer_handler as handler for the signal SIGALRM(TIMER)
    //and clear the list of signals to block during 
    //the handler execution
    act[1].sa_flags = 0;
    act[1].sa_handler = timer_handler;
    sigemptyset(&act[1].sa_mask);
    sigaction(SIGALRM, &act[1], NULL);

    //set handler abort
    act[2].sa_flags = 0;
    act[2].sa_handler = vintr_handler;
    sigemptyset(&act[2].sa_mask);
    sigaction(SIGINT, &act[2], NULL);
    
    while(1){
        //schedule alarm after 10 seconds
        alarm(TIMER_PERIOD);
        pause();
    }
}