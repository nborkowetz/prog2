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

#include <stdlib.h>
#include <sys/stat.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


/****************************************************************
 * PRIVATE FUNCTIONS
 ****************************************************************/

/****************************************************************
 * @brief  check if the substring "exit" exist in a string
 * @param  string the string to be checked
 * @return a pointer to the first occurrence of the pattern  
 ****************************************************************/
char *findExitPattern(char string[]){
    const char PATTERN[] = "exit";
    
    return strstr(string, PATTERN);
}

/****************************************************************
 * @brief  replace the first occurrence of the
 *         character '\n' with '\0'
 * @param  string pointer to the string to be modified
 * @return -  
 ****************************************************************/
void removeNewLine(char *string){
    int i = 0;

    while(*(string + i) != '\n'){
        i++;
    }

    *(string + i) = '\0';
}

/****************************************************************
 * MAIN
 ****************************************************************/

int main(int argc, char *argv[]){
    struct termios attr0;

    char dev0[20], dev1[20], buffer[100];
    int descriptor[2], buffer_size = 100;

    // reading terminal (the user write here) 
    write(STDOUT_FILENO, "insert first device: ", 22);
    read(STDIN_FILENO, &dev0, 20);
    
    //remove the character '\n' from the device path
    removeNewLine(dev0); 
    descriptor[0] = open(dev0, O_RDONLY);

    if(descriptor[0] < 0){
        write(STDOUT_FILENO, "error \n", 8);
        exit(EXIT_FAILURE);
    }

    //writing terminal 
    write(STDOUT_FILENO, "insert second device: ", 22);
    read(STDIN_FILENO, &dev1, 20);
    
    //remove the character '\n' from the device path
    removeNewLine(dev1);

    descriptor[1] = open(dev1, O_RDWR);

    if(descriptor[1] < 0){
        write(STDOUT_FILENO, "error \n", 8);
        exit(EXIT_FAILURE);
    }

    if(tcgetattr(descriptor[0], &attr0) == 0){
        attr0.c_lflag |= ICANON;
        if(tcsetattr(descriptor[0], TCSADRAIN, &attr0) != 0){
            write(STDOUT_FILENO, "error \n", 8);
            exit(EXIT_FAILURE);
        }
    } else {
        write(STDOUT_FILENO, "error \n", 8);
        exit(EXIT_FAILURE);
    }

    while(1){
        int bytes_read = 0;
        
        bytes_read = read(descriptor[0], &buffer, buffer_size);
        if(bytes_read > 0){
            //check if the string "exit" is present in the buffer
            if(findExitPattern(buffer) == NULL){
                write(descriptor[1], &buffer, bytes_read);
            } else {
                write(STDOUT_FILENO, "exiting \n", 10);
                exit(EXIT_SUCCESS);
            }
        }
    }
}