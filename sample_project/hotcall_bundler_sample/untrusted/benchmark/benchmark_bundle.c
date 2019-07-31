#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include "sample.h"
#include "hotcall-hash.h"
#include "hotcall.h"
#include <x86intrin.h>

/*
  These experiments demonstrates the possible performance gains from bundling hotcalls together
*/

unsigned int
benchmark_hotcall_sz_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[512] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[512];
    create_file_name(file_name, "hotcall_sz_1", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}


unsigned int
benchmark_hotcall_bundle_sz_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_sz_1", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_sz_2(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[512] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[512];
    create_file_name(file_name, "hotcall_sz_2", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}


unsigned int
benchmark_hotcall_bundle_sz_2(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_sz_1", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_sz_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_sz_1", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 1;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        BEGIN_FOR(((struct for_config) {
            .n_iters = &n_iters
        }));
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        END_FOR();
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_each_sz_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_each_sz_1", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        unsigned int n_iters = 10000; int x = 0;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }), VAR(x, 'd'));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_sz_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_sz_5", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_bundle_sz_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_sz_5", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_sz_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_sz_5", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 5;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        BEGIN_FOR(((struct for_config) {
            .n_iters = &n_iters
        }));
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        END_FOR()
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_each_sz_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_each_sz_5", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 5;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(((struct for_each_config) { .function_id = hotcall_ecall_test_func_0, .n_iters = &n_iters }));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_sz_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_sz_10", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_bundle_sz_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_sz_10", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_sz_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_sz_10", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 10;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        BEGIN_FOR(((struct for_config) {
            .n_iters = &n_iters
        }));
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        END_FOR()
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_each_sz_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_each_sz_10", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 10;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(((struct for_each_config) { .function_id = hotcall_ecall_test_func_0, .n_iters = &n_iters }));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_sz_25(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_sz_25", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_bundle_sz_25(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_sz_25", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_sz_25(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_sz_25", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 25;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        BEGIN_FOR(((struct for_config) {
            .n_iters = &n_iters
        }));
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        END_FOR();
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_each_sz_25(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_each_sz_25", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 25;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(((struct for_each_config) { .function_id = hotcall_ecall_test_func_0, .n_iters = &n_iters }));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_sz_50(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_sz_50", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_bundle_sz_50(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_sz_50", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_sz_50(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_sz_50", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 50;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        BEGIN_FOR(((struct for_config) {
            .n_iters = &n_iters
        }));
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        END_FOR();
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_each_sz_50(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_each_sz_50", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 50;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(((struct for_each_config) { .function_id = hotcall_ecall_test_func_0, .n_iters = &n_iters }));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_sz_100(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_sz_100", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_bundle_sz_100(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_sz_100", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_sz_100(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_sz_100", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 100;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        BEGIN_FOR(((struct for_config) {
            .n_iters = &n_iters
        }));
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(x, 'd'));
        END_FOR();
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_for_each_sz_100(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    create_file_name(file_name, "hotcall_bundle_for_each_sz_100", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE); int x = 0;
        unsigned int n_iters = 100;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(((struct for_each_config) { .function_id = hotcall_ecall_test_func_0, .n_iters = &n_iters }));
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
