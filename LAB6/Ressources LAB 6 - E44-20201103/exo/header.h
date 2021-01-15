#include <pthread.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#if defined(_WIN32)
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h> /* POSIX flags */
#include <sys/time.h>   /* gethrtime(), gettimeofday() */
#include <time.h>   /* clock_gettime(), time() */

#if defined(__MACH__) && defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif

#else
#error "Unable to define getRealTime( ) for an unknown OS."
#endif




void sort_partial(int* start, int* end);
void merge(int *s1, int *e1, int* s2, int* e2);
void shuffle(int * b, int size);
double getRealTime();
