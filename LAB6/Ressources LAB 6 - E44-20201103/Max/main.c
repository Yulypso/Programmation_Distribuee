#include "header.h"

#define SIZE_ARRAY 100000000

struct context
{
    int * ptr_start;
    int * ptr_end;
    int index_demarrage;
    int nb_thread;
    int max;
};

pthread_t *tid;

int max_partial(int* s, int* e)
{
    int max = 0;
    while(s < e)
    {
        if (*s > max) max = *s;
        s++;
    }
    return max;
}

void* max_thread(void* arg)
{
    struct context *ctx = arg;
    int nombre_iteration = ceil(log2(ctx->nb_thread));
    // Max partiel
    ctx->max = max_partial(ctx->ptr_start, ctx->ptr_end);

    int it;
    for (it = 0; it < nombre_iteration; ++it)
    {
        if (ctx->index_demarrage % (2 << it) == 0)
        {
            int thread_waited = ctx->index_demarrage + (1 << it);
            if (thread_waited >= ctx->nb_thread) return ctx;

            // Attente du thread
            struct context *ctx_merge;
            assert(pthread_join(tid[thread_waited], (void**)&ctx_merge) == 0);

            // Fusion des threads voisin
            if (ctx_merge->max > ctx->max) ctx->max = ctx_merge->max;
            free(ctx_merge);
        }
        else
        {
            return ctx;
        }
    }
    return ctx;
}

int max(int* tab, size_t nb_elem, int nb_thread)
{
    int elem_by_thread = ceil((double)SIZE_ARRAY/nb_thread);
    tid = malloc(nb_thread * sizeof(pthread_t));
    // Création des threads
    int i;
    for (i = nb_thread - 1; i >= 0; --i)
    {
        struct context *ctx = malloc(sizeof(struct context));

        ctx->ptr_start = tab + i * elem_by_thread;
        ctx->ptr_end = tab + (i + 1) * elem_by_thread;
        if (ctx->ptr_end > tab + nb_elem) ctx->ptr_end = tab + nb_elem;
        ctx->index_demarrage = i;
        ctx->nb_thread = nb_thread;
        assert(pthread_create(&tid[i], NULL, max_thread, ctx) == 0);
    }
    struct context *ctx;
    assert(pthread_join(tid[0], (void**)&ctx) == 0);
    int max = ctx->max;
    free(ctx);
    free(tid);
    return max;
}

void shuffle(int * b, int size)
{
    srand(time(NULL));
    int i;
    for (i = 0; i < size/2; ++i)
    {
        int first = rand() % size;
        int second = rand() % size;
        int tmp = b[first];
        b[first] = b[second];
        b[second] = tmp;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s nb_thread\n", argv[0]);
        exit(-1);
    }
    int nb_thread = atoi(argv[1]);
    int *buffer = malloc(sizeof(int) * SIZE_ARRAY);
    int i;
    for (i = 0; i < SIZE_ARRAY; ++i)
    {
        buffer[i] = i ;
    }
    shuffle(buffer, SIZE_ARRAY);

    double startTime, endTime;
    startTime = getRealTime();

    int m = max(buffer, SIZE_ARRAY, nb_thread);

    endTime = getRealTime();
    printf("Max : %d\n", m);

    free(buffer);
    fprintf(stderr, "Real time used = %lf\n", (endTime - startTime));
    return 0;
}
