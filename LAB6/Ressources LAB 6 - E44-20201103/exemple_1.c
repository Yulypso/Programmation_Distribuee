#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SIZE_FIFO 7
#define NB_PROD 1
#define NB_CONSO 1
#define NB_MESSAGE 2000

int min(int a, int b) {
    return a < b ? a : b;
}

// Structure Fifo communication entre consommateurs et producteurs
struct fifo {
    int tab[SIZE_FIFO]; // Tableau d'elements en attente
    int ptr_lecteur;    // Index de la prochaine case a lire
    int ptr_ecrivain;   // Index de la prochaine case a ecrire
    int nb_elem;        // Nombre d'element present dans la fifo
} fifo;

// Fonction d'initialisation de la fifo
void init_fifo(struct fifo *f) {
    f->nb_elem = 0;
    f->ptr_lecteur = 0;
    f->ptr_ecrivain = 0;
}

// Fonction permettant d'inserer une valeur dans la fifo
void put(struct fifo *f, int a) {
    while (f->ptr_lecteur == f->ptr_ecrivain && f->nb_elem != 0){
    
    }

    f->tab[f->ptr_ecrivain] = a;
    f->ptr_ecrivain = (f->ptr_ecrivain + 1) % SIZE_FIFO;
    f->nb_elem++;
}

// Fonction permettant de recuperer une valeur depuis la fifo
int get(struct fifo *f) {
    int value;
    while (f->nb_elem == 0) {

    }

    value = f->tab[f->ptr_lecteur];
    f->ptr_lecteur = (f->ptr_lecteur + 1) % SIZE_FIFO;
    f->nb_elem--;

    return value;
}

// Fonction de production
void *prod(void* arg) {
    long nombre_de_message = (long)arg;
    while(nombre_de_message--) {
        int value = rand() % 1000;
        printf("Produced %d\n", value);
        put(&fifo, value);
    }
    pthread_exit(NULL);
}

// Fonction de consommation
void *conso(void* arg) {
    long nombre_de_message = (long)arg;
    while(nombre_de_message--) {
        int value = get(&fifo);
        printf("\t\t\t\tReceived %d\n", value);
    }
    pthread_exit(NULL);
}

// Fonction principale
int main() {
    long i;
    pthread_t prod_id[NB_PROD];
    pthread_t conso_id[NB_CONSO];
    
    init_fifo(&fifo);
    
    long nb_message_left = NB_MESSAGE;
    for (i = 0; i < NB_PROD; i++) {
        long nb_message = NB_MESSAGE/NB_PROD;
        if (i == NB_PROD - 1) nb_message = nb_message_left;
        pthread_create(&prod_id[i], NULL, prod, (void*)nb_message);
        nb_message_left -= nb_message;
    }
    
    nb_message_left = NB_MESSAGE;
    for (i = 0; i < NB_CONSO; i++) {
        long nb_message = NB_MESSAGE/NB_CONSO;
        if (i == NB_CONSO - 1) nb_message = nb_message_left;
        pthread_create(&conso_id[i], NULL, conso, (void*)nb_message);
        nb_message_left -= nb_message;
    }
    
    for (i = 0; i < NB_PROD; i++) {
        pthread_join(prod_id[i], NULL);
    }
    
    for (i = 0; i < NB_CONSO; i++) {
        pthread_join(conso_id[i], NULL);
    }
    return 0;
}