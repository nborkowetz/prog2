
#include <stdlib.h>
#include <sys/stat.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


char *findExitPattern(char string[]){
    const char PATTERN[] = "exit";
    
    return strstr(string, PATTERN);
}

void removeNewLine(char *string){
    int i = 0;

    while(*(string + i) != '\n'){
        i++;
    }

    *(string + i) = '\0';
}

int main(int argc, char *argv[]){
    pid_t pid[2];

    int pid_nr = sizeof(pid) / sizeof(pid[0]);

    const char *path  = "/usr/bin/xterm";
    char *const arg[]   = {"xterm", NULL};
    
    struct termios attr0;

    char dev0[20], dev1[20], buffer[100];
    int descriptor[2], buffer_size = 100;
    int status;

    //creazione dei filgli
    pid[0] = fork();
    

    if(pid[0] < 0 ){
        write(STDOUT_FILENO, "error \n", 8);
        exit(EXIT_FAILURE);
    } 
    else if(pid[0] == 0 ) {
        status = execv("/usr/bin/xterm", arg);
        if(status == -1){
            write(STDOUT_FILENO, "error with execv\n", 18);
        }
    }
    else {
        pid[1] = fork();

        if(pid[1] < 0 ){
            write(STDOUT_FILENO, "error \n", 8);
            exit(EXIT_FAILURE);
        } 
        else if(pid[1] == 0 ) {
            status = execv("/usr/bin/xterm", arg);
            if(status == -1){
                write(STDOUT_FILENO, "error with execv\n", 18);
            }
        }
        else{
            // terminale per la scrittura dei comandi 
            write(STDOUT_FILENO, "insert first device: ", 22);
            read(STDIN_FILENO, &dev0, 20);
            removeNewLine(dev0);

            descriptor[0] = open(dev0, O_RDONLY);

            if(descriptor[0] < 0){
                write(STDOUT_FILENO, "error \n", 8);
                exit(EXIT_FAILURE);
            }

            // terminale per la visulalizzazione dei comandi 
            write(STDOUT_FILENO, "insert second device: ", 22);
            read(STDIN_FILENO, &dev1, 20);
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
                    if(findExitPattern(buffer) == NULL){
                        write(descriptor[1], &buffer, bytes_read);
                    } else {
                        write(STDOUT_FILENO, "exiting \n", 10);
                        exit(EXIT_SUCCESS);
                    }
                }
            }
        }   
    }
}