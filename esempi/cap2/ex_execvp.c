/* ex_execvp */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    strcpy(argv[0], "cal");
    execvp("cal", argv);
    printf("\n\nDone...\n");
}
