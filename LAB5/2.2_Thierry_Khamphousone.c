/* Thierry Khamphousone - TC-44 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 10 //number of tasks 

long global_result = 0;
pthread_mutex_t mutex;

void* sum_global_result(void* num)
{
	long val = (long) num;
	printf("thread n°: %ld\n", val);
	pthread_mutex_lock(&mutex);
	global_result += val;
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	pthread_t* threads;
	threads = malloc(N * sizeof(threads));

	for(long i=0; i<N; i++)
	{
		if(pthread_create(&threads[i], NULL, sum_global_result, (void*)i))
		{
			perror("pthread_create: ");
			return EXIT_FAILURE; 
		}
	}

	for(long j=0; j<N; j++)
	{
		if(pthread_join(threads[j], NULL))
		{
			perror("pthread_join: ");
			return EXIT_FAILURE; 
		}
	}
	printf("all threads have finished running\n");
	printf("global_result: %ld\n", global_result);

	pthread_exit(NULL);
	free(threads);
	return EXIT_SUCCESS;
}