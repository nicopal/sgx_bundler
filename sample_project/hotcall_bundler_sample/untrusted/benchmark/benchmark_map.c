#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"

unsigned int
benchmark_map(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds) {
    unsigned int warmup = n_rounds / 10;
    char out_dir[] = "./data/";
    char file_name[64];
    char line[64];
    unsigned int t;
    FILE *f;


    /*unsigned int n_vals = 6, n_iters;
    int n_iterations[n_vals] = { 10, 25, 100, 500, 1000, 10000 };
    for(int j = 0; j < n_vals; ++j) {
        n_iters = n_iterations[j];
        sprintf(file_name, "./data/map_%d\n", n_iters);
        f = fopen(file_name, "w");
        for(int iter = 0; iter < n_iters; ++iter) {
            for(int i = 0; i < (n_rounds + warmup); ++i) {
                clear_cache();
                int x[n_iters] = { 0 };
                int ys[n_iters] = { 0 };
                BEGIN
                BUNDLE_BEGIN();
                MAP(((struct map_config) {
                        .function_id = hotcall_ecall_plus_one_ret,
                        .n_iters = &n_iters
                    }),
                    VECTOR(x, 'd'),
                    VECTOR(ys, 'd')
                );
                hotcall_bundle_end(sm_ctx);
                CLOSE
                if(i >= warmup) {
                    t = GET_TIME
                    int n = sprintf(line, "%u\n", t);
                    fwrite(line, 1, n, f);
                }
            }
        }
        fclose(f);
    }*/
    //qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return 0;///ounds[n_rounds / 2];

}
