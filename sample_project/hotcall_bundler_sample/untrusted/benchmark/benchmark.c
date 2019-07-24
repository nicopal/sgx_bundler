#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

volatile long unsigned dummy[L1_CACHE_SIZE];

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
benchmark_v2(struct shared_memory_ctx *sm_ctx, unsigned int (*f_benchmark)(struct shared_memory_ctx *, unsigned int, unsigned int, bool), unsigned int n_rounds, unsigned int n_iters, bool cold_cache) {
    unsigned int r, avg_median = 0;
    for(int n = 0; n < n_iters; ++n) {
        printf("Running iteration %d, cold cache: %s\n", n, cold_cache ? "true" : "false");
        r = f_benchmark(sm_ctx, n_rounds, n, cold_cache);
        printf("%d\n", r);
        avg_median += r;
    }
    printf("Median %u\n", avg_median/n_iters);
}

int
cmpfunc (const void * a, const void * b) {
   return ( *(unsigned int*)a - *(unsigned int*)b );
}

void
clear_cache() {
    memset((void *) dummy, 1, 8 * L1_CACHE_SIZE);
}
