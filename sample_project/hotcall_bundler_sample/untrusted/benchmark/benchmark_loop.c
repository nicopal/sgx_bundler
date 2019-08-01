#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include <stdarg.h>
#include "postfix_translator.h"
#include "hotcall_bundler_sample_u.h"
#include "sample.h"
#include <x86intrin.h>


/*
*   When to use which loop? Some pieces of code might not be possible to write with only iterators.
*   General conclusion: use iterators over loops whenever possible. This hints towards that using a functional programming stýle when
*   interacting with enclave is prefereable in comparison to an imperativ programming style since a functional programming style uses operators which
*   uses iterators and no loops.
*
*   However, there might be cases where a piece of code cannot be transformed into functional code. For instance, the closes one can get to a translation of a classic imperativ while loop
*   is to use recursion, the only functional operators that my library supports are filters, for each and maps and hence there is no natural translation of while loops
*   and hence there are cases where one is forced to use the looping approach or perhaps rewrite the original code.
*
*
*/

unsigned int
benchmark_hotcall_loop_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 };
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
            BEGIN_FOR(((struct for_config) {
                .n_iters = &n_iters
            }));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
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
benchmark_hotcall_loop_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 };
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
            BEGIN_FOR(((struct for_config) {
                .n_iters = &n_iters
            }));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
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
benchmark_hotcall_loop_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 };
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
            BEGIN_FOR(((struct for_config) {
                .n_iters = &n_iters
            }));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
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
benchmark_hotcall_loop_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 };
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
            BEGIN_FOR(((struct for_config) {
                .n_iters = &n_iters
            }));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
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
benchmark_hotcall_iterator_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 };
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
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
benchmark_hotcall_iterator_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 };
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
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
benchmark_hotcall_iterator_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 };
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
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
benchmark_hotcall_iterator_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 };
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
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
benchmark_hotcall_loop_filter(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 }, x = 0;
        s = __rdtscp(aux);
        for(int j = 0; j < n_iters; ++j) {
            HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(xs[j], 'u'));
            if(xs[j] > x) {
                HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_plus_one), VAR(xs[j], 'u'));
            }
        }
        /*BUNDLE_BEGIN();
            BEGIN_FOR(((struct for_config) {
                .n_iters = &n_iters
            }));
                HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                IF(((struct if_config) {
                    .predicate_fmt = "u>u"
                }), VECTOR(xs, 'u'), VAR(x, 'u'));
                THEN
                    HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_plus_one), VECTOR(xs, 'u'));
                END
            END_FOR();
        BUNDLE_END();*/
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        for(int j = 0; j < n_iters; ++j) {
            if(xs[j] != 2) printf("wrong value %u\n", xs[j]);
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_iterator_filter(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
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
        unsigned int n_iters = 20, xs[n_iters] = { 0 }, x = 0, ys[n_iters], out_length;
        s = __rdtscp(aux);
        BUNDLE_BEGIN();
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &n_iters }),
            VECTOR(xs, 'u')
        );
        FILTER(((struct filter_config) {
            .predicate_fmt = "u>u"
        }), VECTOR(xs, 'u', &n_iters), VAR(x, 'u'), VECTOR(ys, 'u', &out_length));
        FOR_EACH(
            ((struct for_each_config) { .function_id = hotcall_ecall_plus_one, .n_iters = &out_length }),
            VECTOR(ys, 'u')
        );
        BUNDLE_END();
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(out_length != n_iters) printf("wrong length\n");
        for(int j = 0; j < out_length; ++j) {
            if(ys[j] != 2) printf("wrong value\n");
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
