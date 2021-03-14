/* ex_write_file.c */

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void main (void)
{
    int fd;
    char text[11];
    int retval;

    fd = open("ex_write_text.txt", O_RDWR | O_CREAT, 
              S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
    if(fd < 0){
        write(STDERR_FILENO, "Errore apertura file", 20);
        return;
    }
    lseek(fd, 0, SEEK_END);

    write(STDOUT_FILENO, "Inserisci testo: ", 17);
    retval = (int)read(STDIN_FILENO, text, 10);

    write(STDOUT_FILENO, text, retval);
    write(fd, text, retval);

    close(fd);
}
