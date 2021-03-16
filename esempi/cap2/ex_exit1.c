/* ex_exit1 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void esci1()
{
    printf("Ciao\n");
}

void esci2()
{
    printf("a tutti\n");
}

int main(int argc, char *argv[])
{
    printf("Main...\n");
    atexit(&esci2);
    atexit(&esci1);
    printf(".........\n");
    sleep(5);
    //exit(EXIT_SUCCESS);
    //exit(EXIT_FAILURE);
    //return 10;
    //abort();
}
