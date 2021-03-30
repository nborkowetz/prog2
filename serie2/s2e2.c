/****************************************************************
 * @file    s1e1.c
 * @date    30.03.21
 * @version 1.0
 * @author  Nicola Borkowetz
 * 
 ****************************************************************
 * 
 * @brief   exercise 2 of the serie2 
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

#include <stdio.h>

#define DELAY_CONST  1000000
#define PRINT_DEL_US 500000
#define ERR_STR      "error\n"

const char message[] = "Ciao\n";

int status = 0;
/****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/

/****************************************************************
 * @brief  thread 1: increment by 1 the global variable var
 * @param  -
 * @return -  
 ****************************************************************/
void* print(void *arg){
   pthread_t *thread = (pthread_t*)arg; 

   if(pthread_self() == thread[status]){
       printf("%s", message[status]);
       status++;
   }
}

/****************************************************************
 * MAIN
 ****************************************************************/

int main(int argc, char *argv[]){
    
    pthread_t threads[5];

    //create the threads
    for(int i = 0; i < 5; i++){
        pthread_create(&threads[i], NULL, print, (void*)threads);
    }  

    while(1);
}