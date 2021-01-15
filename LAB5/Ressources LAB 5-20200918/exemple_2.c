#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NB_THREADS 5

void* thread(void* arg) {
    long i = (long)arg;
    sleep(1);
    printf("Bonjour, j'ai reçu %ld\n", i);
    pthread_exit((void*)NULL);
}

int main() {
    long i;
    pthread_t pid[NB_THREADS];
    for (i = 0; i < NB_THREADS; i++) {
        pthread_create(&pid[i], NULL, thread, (void*)i);
    }
    sleep(5);
    printf("Fin du thread principal\n");
    return EXIT_SUCCESS;
}