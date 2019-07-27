#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"

unsigned int
benchmark_map(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "map", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int n_iters = 10000;
    int xs[n_iters] = { 0 }, ys[n_iters] = { 0 };
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        BEGIN
        BUNDLE_BEGIN();
        MAP(((struct map_config) {
                .function_id = hotcall_ecall_plus_one_ret,
                .n_iters = &n_iters
            }),
            VECTOR(xs, 'd'),
            VECTOR(ys, 'd')
        );
        BUNDLE_END();
        CLOSE
        if(i >= warmup) {
            rounds[i - warmup] = GET_TIME
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_for_each(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "map", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int n_iters = 10000;
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int xs[n_iters] = { 0 };
        BEGIN
        BUNDLE_BEGIN();
        FOR_EACH(((struct for_each_config) {
                .function_id = hotcall_ecall_plus_one,
                .n_iters = &n_iters
            }),
            VECTOR(xs, 'd'),
        );
        BUNDLE_END();
        CLOSE
        if(i >= warmup) {
            rounds[i - warmup] = GET_TIME
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
