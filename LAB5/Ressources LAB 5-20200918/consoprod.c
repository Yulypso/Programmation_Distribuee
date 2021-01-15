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
    int tab[SIZE_FIFO]; // Tableau d'elements stockes
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
    
    /* TO BE COMPLETED */
    
}

// Fonction de consommation
void *conso(void* arg) {
    
    /* TO BE COMPLETED */

}

// Fonction principale
int main() {

    /* TO BE COMPLETED */
    
    return 0;
}
