/****************************************************************
 * @file    s2e2b.c
 * @date    30.03.21
 * @version 1.0
 * @author  Nicola Borkowetz
 * 
 ****************************************************************
 * 
 * @brief   exercise 2b of the serie2 
 *          (course of coucurrent and event-driven programming)
 *          
 *          the aim is to:
 *              -ask the path for two terminals 
 *              -read the typed strings in the first 
 *               terminal and write them in the second one.
 *              -end the program if the strig "exit" is typed
 *          
 *          only I/O POSIX functions are allowed
 * 
 ****************************************************************/
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define DELAY_CONST  100000
#define ERR_STR      "error\n"

const char message[] = "Ciao\n";

pthread_mutex_t mutex;
pthread_cond_t  var_cond;

/****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/

/****************************************************************
 * @brief  thread 1: increment by 1 the global variable var
 * @param  -
 * @return -  
 ****************************************************************/
void* print(void *position){
    int pos = (int) position;

    pthread_mutex_lock(&mutex);
    
    while(1){
        while(status != pos);

        //printf("%c", message[pos]);
        write(STDOUT_FILENO, &message[pos], 1);
        usleep(DELAY_CONST);    
        if(status < 4){
            status++;
        } else {
            status = 0;
        }
    }
}

/****************************************************************
 * MAIN
 ****************************************************************/

int main(int argc, char *argv[]){
    pthread_t threads[5];

    //init mutex and condition variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&var_cond, NULL);

    //create the threads
    for(int i = 0; i < 5; i++){
        if(pthread_create(&threads[i], NULL, print, (void *)i) != 0){
            write(STDOUT_FILENO, ERR_STR, 6);
        }
    }  

    for(int i = 0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_cond_destroy(&var_cond);
    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
}

