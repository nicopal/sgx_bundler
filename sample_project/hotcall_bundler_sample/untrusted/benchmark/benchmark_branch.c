#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include <stdarg.h>
#include "postfix_translator.h"
#include "hotcall_bundler_sample_u.h"
#include "sample.h"
#include <x86intrin.h>


/*

    The following benchmarks gives several imporant insites about when it's wise to use a branching statement inside of enclave and when it's a better idea evaluate an if statement outside of the enclave.

    General conclusion: Only use an if statement if the if statement is nested inside a loop. The only time case when evaluating an if statement inside an enclave when it is not
    inside of a loop is when the if statement is true and the cache is hot. In all other cases, the overhead of creating the execution graph and evaluating the condition exceeds the cost
    of leaving and entering the enclave.

    If the if statement is inside of a loop and the loop has more than a single iteration in the common case, it is a good idea to evaluate if statements inside of enclave.

    The reasons for this is:

    1. The execution graph only needs to be created once, it is a one time payment.
    2. All of the execution graph + all of the values needed to evaluate the condition will be in inside the CPU cache after the first iteration which means that all subsecuent iterations
        will be much faster than the first iteration.
*/

unsigned int
benchmark_hotcall_branch_true_naive(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_branch_true_naive", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        bool res1, res2 = false;
        unsigned int n_iters = 5;
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res1, 'b'));
        if(res1) {
            HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res2, 'b'));
        }
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(!res2) printf("wrong answer\n");
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_branch_true_naive_loop(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_branch_true_naive_loop", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        bool res1, res2 = false;
        unsigned int n_iters = 2;
        for(int j = 0; j < n_iters; ++j) {
            HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res1, 'b'));
            if(res1) {
                HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res2, 'b'));
            }
        }
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(!res2) printf("wrong answer\n");
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_branch_true(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_branch_true", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        bool res1, res2 = false;
        unsigned int n_iters = 5;
        BUNDLE_BEGIN();

        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res1, 'b'));
        IF((struct if_config) { .predicate_fmt = "b"}, VAR(res1, 'b'));
        THEN
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res2, 'b'));
        END
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(!res2) printf("wrong answer\n");
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_branch_true_loop(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_branch_true_loop", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        bool res1, res2 = false;
        unsigned int n_iters = 2;
        BUNDLE_BEGIN();
        BEGIN_FOR(((struct for_config) {
            .n_iters = &n_iters
        }));
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res1, 'b'));
        IF((struct if_config) { .predicate_fmt = "b"}, VAR(res1, 'b'));
        THEN
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res2, 'b'));
        END
        END_FOR();
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(!res2) printf("wrong answer\n");
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_branch_false_naive(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_branch_false_naive", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        bool res1, res2 = false;
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_always_false), VAR(res1, 'b'));
        if(res1) {
            HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res2, 'b'));
        }
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(res2) printf("wrong answer\n");
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_branch_false_naive_loop(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_branch_false_naive_loop", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        bool res1, res2 = false;
        unsigned int n_iters = 2;
        for(int j = 0; j < n_iters; ++j) {
            HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_always_false), VAR(res1, 'b'));
            if(res1) {
                HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res2, 'b'));
            }
        }
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(res2) printf("wrong answer\n");
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_branch_false(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_branch_false", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        bool res1, res2 = false;
        unsigned int n_iters = 2;
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_always_false), VAR(res1, 'b'));
        IF((struct if_config) { .predicate_fmt = "b"}, VAR(res1, 'b'));
        THEN
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res2, 'b'));
        END
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(res2) printf("wrong answer\n");
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_branch_false_loop(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall_branch_false_loop", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
	unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        s = __rdtscp(aux);
        bool res1, res2 = false;
        unsigned int n_iters = 2;
        BUNDLE_BEGIN();
        HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_always_false), VAR(res1, 'b'));
        IF((struct if_config) { .predicate_fmt = "b"}, VAR(res1, 'b'));
        THEN
            HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_always_true), VAR(res2, 'b'));
        END
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(res2) printf("wrong answer\n");
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
