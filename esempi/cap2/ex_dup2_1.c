/* ex_dup2_1 */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fildes;

    fildes = open("test_dup2_1.txt", O_APPEND | O_WRONLY | O_CREAT,
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if(fildes < 0)
        return 1;

    if(dup2(fildes, STDOUT_FILENO) < 0)
        return 1;

    system("ls -l");

    return 0;
}
