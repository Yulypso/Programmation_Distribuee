#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NB_THREADS 5

void* thread(void* arg) {
    //pthread_detach(pthread_self());
    long i = (long)arg;
    sleep(1);
    printf("Bonjour, j'ai reçu %ld\n", i);
    long * tmp = malloc(sizeof(long));
    *tmp = i;
    pthread_exit((void*)tmp);
}

int main() {
    long i;
    pthread_t pid[NB_THREADS];
    for (i = 0; i < NB_THREADS; i++) {
        pthread_create(&pid[i], NULL, thread, (void*)i);
    }
    for (i = 0; i < NB_THREADS; i++) {
        long* a;
        pthread_join(pid[i], (void**)&a);
        printf("Le thread %ld s'est terminé en renvoyant %ld\n", i, *a);
    }
    printf("Fin du thread principal\n");
    return EXIT_SUCCESS;
}
