#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include <stdarg.h>
#include "postfix_translator.h"
#include "hotcall_bundler_sample_u.h"
#include "sample.h"
#include <x86intrin.h>

/*
*   What is the effect on the number of arguments ?
*   We can see that the number of arguments of a function increases the execution time of a HCALL.
*   A function which does nothing andtakes 15 arguments takes roughly twice as long to execute in comparison
*   to a function which does nothing and take no arguments.
*
*   The results suggest that ít might be wiser to replace functions which has a lot of arguments with a struct instead.
*
*
*   A previous study (Virtualization) clears cache by writing a file of the same size as the system's LLC. However, based on observations from an experiment
*   writing a block with the same size of LLC is not enough, writing a block with size of LLC evict some values of the cache but some values are still in L3 cache.
*   In order for me to completly evict the entire cache I had to write a larger block.
*/

unsigned int
benchmark_hotcall_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_0", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_0));
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
benchmark_vanilla_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "vanilla_0", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        ecall_test_func_0(global_eid);
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
benchmark_hotcall_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_1", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_1), VAR(x, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "vanilla_1", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 0;
        s = __rdtscp(aux);
        ecall_test_func_1(global_eid, x);
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;

        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_3", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 0, y = 0, z = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_3), VAR(x, 'd'), VAR(y, 'd'), VAR(z, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;

        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "vanilla_3", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 0, y = 0, z = 0;
        s = __rdtscp(aux);
        ecall_test_func_3(global_eid, x, y, z);
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;

        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_5", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e;
        a = b = c = d = e = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(
            CONFIG(.function_id = hotcall_ecall_test_func_5),
            VAR(a, 'd'),
            VAR(b, 'd'),
            VAR(c, 'd'),
            VAR(d, 'd'),
            VAR(e, 'd'),
        );
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;

        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "vanilla_5", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e;
        a = b = c = d = e = 0;
        s = __rdtscp(aux);
        ecall_test_func_5(global_eid, a, b, c, d, e);
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;

        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_10", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e, f, g, h, t, j;
        a = b = c = d = e = f = g = h = t = j = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(
            CONFIG(.function_id = hotcall_ecall_test_func_10),
            VAR(a, 'd'),
            VAR(b, 'd'),
            VAR(c, 'd'),
            VAR(d, 'd'),
            VAR(e, 'd'),
            VAR(f, 'd'),
            VAR(g, 'd'),
            VAR(h, 'd'),
            VAR(t, 'd'),
            VAR(j, 'd')
        );
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;

        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "vanilla_10", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e, f, g, h, t, j;
        a = b = c = d = e = f = g = h = t = j = 0;
        s = __rdtscp(aux);
        ecall_test_func_10(global_eid, a, b, c, d, e, f, g, h, t, j);
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;

        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_15", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e, f, g, h, t, j, l, m, n, o, p;
        a = b = c = d = e = f = g = h = t = j = l = m = n = o = p = 0;
        s = __rdtscp(aux);
        HCALL_SIMPLE(
            CONFIG(.function_id = hotcall_ecall_test_func_15),
            VAR(a, 'd'),
            VAR(b, 'd'),
            VAR(c, 'd'),
            VAR(d, 'd'),
            VAR(e, 'd'),
            VAR(f, 'd'),
            VAR(g, 'd'),
            VAR(h, 'd'),
            VAR(t, 'd'),
            VAR(j, 'd'),
            VAR(l, 'd'),
            VAR(m, 'd'),
            VAR(n, 'd'),
            VAR(o, 'd'),
            VAR(p, 'd'),
        );
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
benchmark_vanilla_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "vanilla_15", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds / 5, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e, f, g, h, t, j, l, m, n, o, p;
        a = b = c = d = e = f = g = h = t = j = l = m = n = o = p = 0;
        s = __rdtscp(aux);
        ecall_test_func_15(global_eid, a, b, c, d, e, f, g, h, t, j, l, m, n, o, p);
        e = __rdtscp(aux);
        if(i >= warmup) {
            t = e - s;
            rounds[i - warmup] = t;

        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
