/* Thierry Khamphousone - TC-44 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define SIZE_FIFO 7
#define NB_PROD 10
#define NB_CONSO 80
#define NB_MESSAGE 2000

// Structure Fifo communication entre consommateurs et producteurs
typedef struct fifo fifo;

struct fifo {
    int tab[SIZE_FIFO]; // Tableau d'elements stockes
    int ptr_lecteur;    // Index de la prochaine case a lire
    int ptr_ecrivain;   // Index de la prochaine case a ecrire
    int nb_elem;        // Nombre d'element present dans la fifo
    int nb_consumed;    //nb de messages déjà consommé
    int nb_producted;   //nb de messages déjà produit
};

pthread_mutex_t mutex;
pthread_cond_t cond; 


int min(int a, int b) {
    return a < b ? a : b;
}

// Fonction d'initialisation de la fifo
void init_fifo(struct fifo *f) {
    f->nb_elem = 0;
    f->ptr_lecteur = 0;
    f->ptr_ecrivain = 0;
    f->nb_consumed = 0;
    f->nb_producted = 0;
}

// Fonction permettant d'inserer une valeur dans la fifo
void put(struct fifo *f, int a) {

    while (f->ptr_lecteur == f->ptr_ecrivain && f->nb_elem != 0){

    }

    f->tab[f->ptr_ecrivain] = a;
    f->ptr_ecrivain = (f->ptr_ecrivain + 1) % SIZE_FIFO;
    f->nb_elem++;
    f->nb_producted++;

    printf("production de %d\n", a);
}

// Fonction permettant de recuperer une valeur depuis la fifo
int get(struct fifo *f) {
    
    int value;
    
    while (f->nb_elem == 0) {
       
    }

    value = f->tab[f->ptr_lecteur];
    f->ptr_lecteur = (f->ptr_lecteur + 1) % SIZE_FIFO;
    f->nb_elem--;
    f->nb_consumed++;

    printf("consommation de %d\n", value);
    return value;
}


// Fonction de production
void *prod(void* arg) {

    fifo* giga_fifo = (fifo*) arg;
    
    pthread_mutex_lock(&mutex);
    if(++giga_fifo->nb_producted < NB_MESSAGE)
    {
        while(giga_fifo->nb_producted < NB_MESSAGE)
        {
            while(!(giga_fifo->nb_elem < SIZE_FIFO))
                pthread_cond_wait(&cond, &mutex);

            if(giga_fifo->nb_elem < SIZE_FIFO)
            {
                int val = rand()%100;
                put(giga_fifo, val);
                pthread_cond_signal(&cond);
            }
        }
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);  
}

//Fonction de consommation
void *conso(void* arg) {

    fifo* giga_fifo = (fifo*) arg;

    pthread_mutex_lock(&mutex);
    if(++giga_fifo->nb_consumed < NB_MESSAGE)
    {
        while(giga_fifo->nb_consumed < NB_MESSAGE)
        {
            while(!(giga_fifo->nb_elem > 0))
                pthread_cond_wait(&cond, &mutex);

            if(giga_fifo->nb_elem > 0)
            {
                get(giga_fifo);
                pthread_cond_signal(&cond);
            }
        }
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

// Fonction principale
int main() {

    srand(time (NULL));
    fifo* giga_fifo = NULL;
    giga_fifo = malloc(sizeof(fifo));
    init_fifo(giga_fifo);

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t* threads_producteurs;
    threads_producteurs = malloc(NB_PROD * sizeof(threads_producteurs));

    pthread_t* threads_consommateurs;
    threads_consommateurs = malloc(NB_CONSO * sizeof(threads_consommateurs));


    for(int i=0; i<NB_PROD; i++)
    {
        if(pthread_create(&threads_producteurs[i], NULL, prod, giga_fifo))
        {
            perror("pthread_create producteurs");
            return EXIT_FAILURE; 
        }
    }

    for(int j=0; j<NB_CONSO; j++)
    {
        if(pthread_create(&threads_consommateurs[j], NULL, conso, giga_fifo))
        {
            perror("pthread_create consommateurs");
            return EXIT_FAILURE; 
        }
    }

    for(int k=0; k<NB_PROD; k++)
    {
        if(pthread_join(threads_producteurs[k], NULL))
        {
            perror("pthread_join: ");
            return EXIT_FAILURE; 
        }
    }

    for(int l=0; l<NB_CONSO; l++)
    {
        if(pthread_join(threads_consommateurs[l], NULL))
        {
            perror("pthread_join: ");
            return EXIT_FAILURE; 
        }
    }

    if(giga_fifo->nb_elem == 0)
        printf("Toute la production a été consommée ;)\n");
    else
        printf("Il reste %d produits :)\n", giga_fifo->nb_elem);
    
    pthread_exit(NULL);
    pthread_mutex_destroy(&mutex);
    free(giga_fifo);
    free(threads_producteurs);
    free(threads_consommateurs);

    return EXIT_SUCCESS;
}
