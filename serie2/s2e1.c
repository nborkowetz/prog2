/****************************************************************
 * @file    s1e1.c
 * @date    22.03.21
 * @version 1.0
 * @author  Nicola Borkowetz
 * 
 ****************************************************************
 * 
 * @brief   exercise 1 of the serie1 
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

#define _GNU_SOURCE

#include <sched.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DELAY_CONST  1000000
#define PRINT_DEL_US 500000
#define ERR_STR      "error\n"

int var = 0;

/****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/

/****************************************************************
 * @brief  delay function
 * @param  -
 * @return - 
 ****************************************************************/
void delay(){
    int i;

    for(i = 0; i <DELAY_CONST; i++);
}

/****************************************************************
 * @brief  thread 1: increment by 1 the global variable var
 * @param  -
 * @return -  
 ****************************************************************/
void* increment(void* unused){
    while(1){
        var++;
        delay();
        //printf("eee\n");
    }
}

/****************************************************************
 * @brief  thread 2: decrement by 1 the global variable var
 * @param  -
 * @return -  
 ****************************************************************/
void* decrement(void* unused){
    while(1){
        var--;
        delay();
    }
}

/****************************************************************
 * MAIN
 ****************************************************************/

int main(int argc, char *argv[]){
    cpu_set_t cpu_set_mask;

    //set the CPU affinity to processor 0 only
    CPU_ZERO(&cpu_set_mask);              //Empty CPU set
    CPU_SET(0, &cpu_set_mask);            //add CPU 0 to the set

    sched_setaffinity(0,                  //current process
                       sizeof(cpu_set_t), //size of cpu_set_t type
                       &cpu_set_mask);    //adress to the CPU mask

    pthread_t thread1, thread2;

    //create thread 1
    pthread_create(&thread1, NULL, increment, NULL);

    //create thread 2
    pthread_create(&thread2, NULL, decrement, NULL);   

    while(1){

        usleep(PRINT_DEL_US);

        //char buffer[33];
        //itoa(var, buffer, 10);
        //write(STDOUT_FILENO, buffer, 10);

        printf("var: %d\n", var);   
    }
}