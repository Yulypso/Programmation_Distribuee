#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SIZE_FIFO 7
#define NB_PROD 5
#define NB_CONSO 3
#define NB_MESSAGE 10

int min(int a, int b) {
    return a < b ? a : b;
}

// Structure Fifo
struct fifo {
    int tab[SIZE_FIFO]; // Tableau permettant de stocker les elements en attente
    int ptr_lecteur;    // Index de la prochaine case a lire
    int ptr_ecrivain;   // Index de la prochaine case a ecrire
    int nb_elem;        // Nombre d'éléments stockés dans la FIFO
    
    pthread_mutex_t mutex;  // AJOUT
    pthread_cond_t vide;    // AJOUT
    pthread_cond_t plein;   // AJOUT
} fifo;

static pthread_once_t once = PTHREAD_ONCE_INIT; // AJOUT

// Fonction d'initialisation de la fifo
void init_fifo(struct fifo *f) {
    f->nb_elem = 0;
    f->ptr_lecteur = 0;
    f->ptr_ecrivain = 0;
    pthread_mutex_init(&f->mutex, NULL);    // AJOUT
    pthread_cond_init(&f->vide, NULL);      // AJOUT
    pthread_cond_init(&f->plein, NULL);     // AJOUT
}

// Fonction permettant d'inserer une valeur dans la fifo
void put(struct fifo *f, int a) {
    pthread_mutex_lock(&f->mutex); // AJOUT
    while (f->ptr_lecteur == f->ptr_ecrivain && f->nb_elem != 0) {
        pthread_cond_wait(&f->vide, &f->mutex); // AJOUT
    }
    
    f->tab[f->ptr_ecrivain] = a;
    f->ptr_ecrivain = (f->ptr_ecrivain + 1) % SIZE_FIFO;
    f->nb_elem++;
    
    pthread_cond_signal(&f->plein); // AJOUT
    
    pthread_mutex_unlock(&f->mutex); // AJOUT
}

// Fonction permettant de recuperer une valeur depuis la fifo
int get(struct fifo *f) {
    int value;
    pthread_mutex_lock(&f->mutex); // AJOUT
    while (f->nb_elem == 0) {
        pthread_cond_wait(&f->plein, &f->mutex); // AJOUT
    }
    
    value = f->tab[f->ptr_lecteur];
    f->ptr_lecteur = (f->ptr_lecteur + 1) % SIZE_FIFO;
    f->nb_elem--;
    
    pthread_cond_signal(&f->vide); // AJOUT
    
    pthread_mutex_unlock(&f->mutex); // AJOUT
    
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