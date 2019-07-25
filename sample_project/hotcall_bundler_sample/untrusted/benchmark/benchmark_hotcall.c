#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include <stdarg.h>
#include "postfix_translator.h"
#include "hotcall_bundler_sample_u.h"
#include "sample.h"


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

static void write_to_file(char *dir_path, char *file_name, unsigned int rounds[], unsigned int n_rounds) {
    create_test_folder(dir_path);
    char file_path[256];
    sprintf(file_path, "%s/%s", dir_path, file_name);
    FILE *fp;
    fp = fopen(file_path, "a");
    for(int i = 0; i < n_rounds; ++i) {
        fprintf(fp, "%u\n", rounds[i]);
    }
    fclose(fp);
}

static void create_file_name(char *name_buf, const char *name, bool cold_cache, unsigned int cache_clear_multiple) {
    sprintf(name_buf, "%s_%s", name, cold_cache ? "cold" : "warm");
    if(cold_cache) sprintf(name_buf, "%s_%u", name_buf, cache_clear_multiple);
}


unsigned int
benchmark_hotcall_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "hotcall", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        BEGIN
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_0));
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
benchmark_vanilla_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "vanilla", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 5, rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        BEGIN
        ecall_test_func_0(global_eid);
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
benchmark_hotcall_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_1";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");


    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 0;
        BEGIN
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_1), VAR(x, 'd'));
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_1";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");


    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 0;
        BEGIN
        ecall_test_func_1(global_eid, x);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_3";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 0, y = 0, z = 0;
        BEGIN
        HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_test_func_3), VAR(x, 'd'), VAR(y, 'd'), VAR(z, 'd'));
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_3";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");


    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 0, y = 0, z = 0;
        BEGIN
        ecall_test_func_3(global_eid, x, y, z);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_5";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e;
        a = b = c = d = e = 0;
        BEGIN
        HCALL_SIMPLE(
            CONFIG(.function_id = hotcall_ecall_test_func_5),
            VAR(a, 'd'),
            VAR(b, 'd'),
            VAR(c, 'd'),
            VAR(d, 'd'),
            VAR(e, 'd'),
        );
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_5";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e;
        a = b = c = d = e = 0;
        BEGIN
        ecall_test_func_5(global_eid, a, b, c, d, e);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_10";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");


    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e, f, g, h, t, j;
        a = b = c = d = e = f = g = h = t = j = 0;
        BEGIN
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
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_10";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e, f, g, h, t, j;
        a = b = c = d = e = f = g = h = t = j = 0;
        BEGIN
        ecall_test_func_10(global_eid, a, b, c, d, e, f, g, h, t, j);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_hotcall_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_hotcall_15";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e, f, g, h, t, j, l, m, n, o, p;
        a = b = c = d = e = f = g = h = t = j = l = m = n = o = p = 0;
        BEGIN
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
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_vanilla_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_dir[] = DATA_PATH "/hotcall/benchmark_vanilla_15";
    char file_path[256];
    sprintf(file_path, "%s/%s", file_dir, cold_cache ? "cold" : "warm");
    create_test_folder(file_dir);

    FILE *fp;
    fp = fopen(file_path, "a");

    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds / 10, t = 0;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int a, b, c, d, e, f, g, h, t, j, l, m, n, o, p;
        a = b = c = d = e = f = g = h = t = j = l = m = n = o = p = 0;
        BEGIN
        ecall_test_func_15(global_eid, a, b, c, d, e, f, g, h, t, j, l, m, n, o, p);
        CLOSE
        if(i >= warmup) {
            t = GET_TIME
            rounds[i - warmup] = t;
            fprintf(fp, "%u\n", t);
        }
    }
    fclose(fp);

    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}


void
variadic_function(int n, ...) {
    va_list args;
    va_start(args, n);

    int x = 0;
    for(int i = 0; i < n; ++i) {
        x += va_arg(args, int);
    }

    va_end(args);
}

unsigned int
benchmark_variadic_function(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds) {
    unsigned int warmup = n_rounds / 10;
    unsigned int rounds[n_rounds];
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        //if(cold_cache) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        BEGIN
        variadic_function(10, 1, 2, 3, 4, 5, 6, 7, 8, 9);
        CLOSE
        if(i >= warmup) {
            rounds[i - warmup] = GET_TIME
        }
    }
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
