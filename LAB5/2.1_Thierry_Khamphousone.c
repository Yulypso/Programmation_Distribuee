/* Thierry Khamphousone - TC-44 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 10 //number of tasks

void* multiply10(void* num)
{
	long val = (long) num;
	printf("thread n°: %ld\n", val);
	pthread_exit((void*) (val*10));
}

int main(int argc, char const *argv[])
{
	pthread_t* threads;
	threads = malloc(N * sizeof(threads));
	void* res_void = NULL;
	long res;

	for(long i=0; i<N; i++)
	{
		if(pthread_create(&threads[i], NULL, multiply10, (void*)i))
		{
			perror("pthread_create: ");
			return EXIT_FAILURE; 
		}
	}

	for(long j=0; j<N; j++)
	{
		if(pthread_join(threads[j], &res_void))
		{
			perror("pthread_join: ");
			return EXIT_FAILURE; 
		}
		res = (long)res_void;
		printf("thread n°%ld returned: %ld\n", j, res);
	}
	printf("all threads have finished running\n");

	pthread_exit(NULL);
	free(threads);
	return EXIT_SUCCESS;
}