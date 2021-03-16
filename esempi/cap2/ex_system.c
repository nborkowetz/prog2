/* ex_system */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("Stampa della directory corrente:\n");
    printf("=========================\n\n");
    system("ls -l --color=auto");
    printf("\n\nProgramma terminato...\n");
}
