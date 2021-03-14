/* fprintf vs write */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    while(1){
        //fprintf(stdout,"x");
        //fflush(stdout);
        write(STDOUT_FILENO,"x",1);
        sleep(1);
    }
}
