/****************************************************************
 * @file    s1e4.c
 * @date    22.03.21
 * @version 1.0
 * @author  Nicola Borkowetz
 * 
 ****************************************************************
 * 
 * @brief   exercise 4 of the serie1 
 *          (course of coucurrent and event-driven programming)
 *          
 *          the aim is to write a command line interpreter that 
 *          keeps a log of command recived (file s1e4.txt)
 * 
 *          only I/O POSIX functions are allowed
 ****************************************************************/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LEN 100

/****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/

/****************************************************************
 * @brief  display the shell prompt
 * @param  -
 * @return -  
 ****************************************************************/
void printPrompt(){
	write(STDOUT_FILENO, "MY_SHELL : ", 12);
}

/****************************************************************
 * @brief  display a welcome message
 * @param  -
 * @return -  
 ****************************************************************/
void printInitMessage(){
    write(STDOUT_FILENO, "**************************************************************\n", 64);
    write(STDOUT_FILENO, "*WELCOME                                                     *\n", 64);
    write(STDOUT_FILENO, "*TYPE A COMMAND AND PRESS 'ENTER'                            *\n", 64);
    write(STDOUT_FILENO, "*EXAMPLE: ls -a                                              *\n", 64);
    write(STDOUT_FILENO, "*TO EXIT TYPE 'exit'                                         *\n", 64);
    write(STDOUT_FILENO, "**************************************************************\n", 64);
}

/****************************************************************
 * @brief  if the string recived is equal to "exit\n"
 * @param  string the string to be checked
 * @return 1 if the string is equal to "exit\n"
 *         0 otherwise  
 ****************************************************************/
int checkExitPattern(char string[]){
    const char EXIT_PATTERN[] = "exit\n";

    int max = strlen(EXIT_PATTERN);

    for(int i = 0; i < max; i++){
        if(EXIT_PATTERN[i] == string[i]){
            return 0;
        }
    }
    return 1; 
}

/****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/
int main(int argc, char *argv[]){
    int descriptor;
    char command[BUFFER_LEN] = "";

    descriptor = open("s1e4.txt", O_CREAT | O_WRONLY);
    if(descriptor < 0){
        write(STDOUT_FILENO, "Error \n", 8);
        exit(EXIT_FAILURE);
    }

    printInitMessage();

    while(1){
        printPrompt();

        int size = read(STDIN_FILENO, &command, BUFFER_LEN);
        write(descriptor, &command, size);       

        if(checkExitPattern(command) == 0){
            write(STDOUT_FILENO, "exiting...\n", 11);
            exit(EXIT_SUCCESS);
        } else {
            system(command);
        }   
    }
}

