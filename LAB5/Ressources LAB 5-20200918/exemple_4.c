#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define NB_TRAVAILLEUR 4

int travail;

void* travailleur(void* arg) {
    printf("Bonjour travailleur \n");
    for (;;) {
        if (travail - 10 >= 0) {
            travail -= 10;
            printf("Travail consomme : %d\n", travail);
        }
        else {
            printf("POLLING\n");
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

void* patron(void* arg) {
    printf("Bonjour patron \n");
    for (;;) {
        travail += 100;
        printf("Travail produit : %d\n", travail);
        sleep(4);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t patron_id;
    pthread_t travailleur_id[NB_TRAVAILLEUR];
    travail = 0;
    pthread_create(&patron_id, NULL, patron, NULL);
    for (int i = 0; i < NB_TRAVAILLEUR; i++) {
        pthread_create(&travailleur_id[i], NULL, travailleur, NULL);
    }
    for(;;);
}
