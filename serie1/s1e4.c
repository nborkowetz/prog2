#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define BUFFER_LEN 100

void printPrompt(){
	write(STDOUT_FILENO, "MY_SHELL : ", 12);
}

void printInitMessage(){
    write(STDOUT_FILENO, "**************************************************************\n", 64);
    write(STDOUT_FILENO, "*WELCOME                                                     *\n", 64);
    write(STDOUT_FILENO, "*TYPE A COMMAND AND PRESS 'ENTER'                            *\n", 64);
    write(STDOUT_FILENO, "*EXAMPLE: ls -a                                              *\n", 64);
    write(STDOUT_FILENO, "*TO EXIT TYPE 'exit'                                         *\n", 64);
    write(STDOUT_FILENO, "**************************************************************\n", 64);
}

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


int main(int argc, char *argv[]){
    const char EXIT_PATTERN[] = "exit\n";
    

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

