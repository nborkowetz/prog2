/* ex_execl */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    execl("/usr/bin/cal", "cal", "-3", (char*)0);
    printf("\n\nDone...\n");
}
