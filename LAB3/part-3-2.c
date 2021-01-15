#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

/*Thierry Khamphousone - TC-44*/

int main(int argc, const char *argv[])
{
	struct stat buffer;

	if(argc!=2){
		printf("error, no arguments\n");
		exit(EXIT_FAILURE);
	}

	int res = stat(argv[1], &buffer);
	if(!res)
		printf("command stat success for : %s\n", argv[1]);
	else
		printf("command stat error\n");
									/*man 2 stat*/
	printf("inode : %ld\n", buffer.st_ino); /*st_ino : Inode number */
	printf("creation date : %s\n", ctime(&buffer.st_ctime)); /*st_ctime : time of last status change*/

	return 0;
}