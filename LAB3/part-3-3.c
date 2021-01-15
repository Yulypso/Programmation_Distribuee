#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/unistd.h>

/*Thierry Khamphousone - TC-44*/

int main(int argc, const char *argv[])
{
	if(access(argv[1], F_OK)==0)
		printf("File or dirertory exist\n");
	else
	{
		perror("Error ");
		exit(EXIT_FAILURE);
	}

	if(access(argv[1], R_OK)==0)
		printf("File or dirertory readable\n");
	else
		perror("Readable? : Error ");

	if(access(argv[1], W_OK)==0)
		printf("File or dirertory writable\n");
	else
		perror("Writable? : Error ");

	if(access(argv[1], X_OK)==0)
		printf("File or dirertory executable\n");
	else
		perror("Executable? : Error ");

	return EXIT_SUCCESS;
}