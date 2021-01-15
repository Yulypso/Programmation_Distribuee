#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NB_TRAVAILLEUR 4

int travail;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* travailleur(void *arg) {
    long id = (long)arg;
    printf("Je suis le travailleur %ld\n", id);
    for (;;) {
        pthread_mutex_lock(&mutex);
        while (!(travail > 0)) {
            pthread_cond_wait(&cond, &mutex);
        }
        travail -= 10;
        //        travail = travail > 0 ? travail : 0;
        printf("Travailleur %ld consomme : %d\n", id, travail);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void* patron(void* arg) {
    printf("Je suis le patron !!\n");
    for(;;) {
        pthread_mutex_lock(&mutex);
        travail += 100;
        printf("Travail produit par le patron : %d\n", travail);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }
    return NULL;
}

int main() {
    long i;
    pthread_t patron_id;
    pthread_t travailleur_id[NB_TRAVAILLEUR];
    
    travail = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    
    pthread_create(&patron_id, NULL, patron, NULL);
    for (i = 0; i < NB_TRAVAILLEUR; i++) {
        pthread_create(&travailleur_id[i], NULL, travailleur, (void*)i);
    }
    
    pthread_exit(NULL);
}
