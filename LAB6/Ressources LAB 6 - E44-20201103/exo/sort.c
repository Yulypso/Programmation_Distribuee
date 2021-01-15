#include <stdlib.h>
#include <string.h>
#include "header.h"

int cmp (const void * a, const void * b)
{
   return (*(int*)a - *(int*)b);
}

void sort_partial(int* start, int* end)
{
    qsort(start, end - start, sizeof(int), cmp);
}

void merge(int *s1, int *e1, int* s2, int* e2)
{
    int *start = s1;

    if (s2 == e2) return;

    assert((e1 - s1) > 0);
    assert((e2 - s2) > 0);

    int size = (e2 - s1);
    int *out = malloc(sizeof(int) * size);
    int *tmpbuf = out;

    while (!(s1 >= e1 || s2 >= e2))
    {
        if (*s1 > *s2)
        {
            *out = *s2;
            ++s2;
        }
        else
        {
            *out = *s1;
            ++s1;
        }
        ++out;
    }

    while(s2 < e2)
    {
        *out = *s2;
        ++out;
        ++s2;
    }

    while(s1 < e1)
    {
        *out = *s1;
        ++out;
        ++s1;
    }

    memcpy(start, tmpbuf, size * sizeof(int));
    free(tmpbuf);
}
