#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
benchmark(struct shared_memory_ctx *sm_ctx, unsigned int (*f_benchmark)(struct shared_memory_ctx *, unsigned int), unsigned int n_rounds, unsigned int n_iters) {
    unsigned int r, avg_median = 0;
    for(int n = 0; n < n_iters; ++n) {
        printf("Running iteration %d.\n", n);
        r = f_benchmark(sm_ctx, n_rounds);
        printf("%d\n", r);
        avg_median += r;
    }
    printf("Median %u\n", avg_median/n_iters);
}

void
benchmark_v2(struct shared_memory_ctx *sm_ctx, unsigned int (*f_benchmark)(struct shared_memory_ctx *, unsigned int, bool, unsigned int, char*), unsigned int n_rounds, unsigned int n_iters, bool cold_cache, unsigned int clear_cache_size, char *suffix) {
    unsigned int r, avg_median = 0;
    for(int n = 0; n < n_iters; ++n) {
        printf("Running iteration %d, cold cache: %s\n", n, cold_cache ? "true" : "false");
        r = f_benchmark(sm_ctx, n_rounds, cold_cache, clear_cache_size, suffix);
        printf("%d\n", r);
        avg_median += r;
    }
    printf("Median %u\n", avg_median/n_iters);
}

int
cmpfunc (const void * a, const void * b) {
   return ( *(unsigned int*)a - *(unsigned int*)b );
}



int memset_s(void *v, int c, size_t n) {
    volatile unsigned char *p = (volatile unsigned char *) v;
    while (n--) {
        *p++ = c;
    }
    return 0;
}

void
clear_cache(char *buf, unsigned int buf_size) {
    memset_s((void *) buf, 1, buf_size);
}
