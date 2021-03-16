/* ex_system_2_bin */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("\nEsecuzione di %s\n", argv[0]);
	sleep(10);
	printf("Esecuzione di %s terminata\n", argv[0]);
}
