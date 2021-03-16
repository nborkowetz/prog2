/* ex_execv */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    strcpy(argv[0], "cal");
    execv("/usr/bin/cal", argv);
    printf("\n\nDone...\n");
}
