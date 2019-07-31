#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include "hotcall-hash.h"
#include <x86intrin.h>


/*

    Benchmark standard hcall execution time for hotcall_ecall_add_and_count
    Benchmark hotcall_ecall_add_and_count with memoization and LRU
    Benchmark hotcall_ecall_add_and_count with memoization and FIFO

    FIFO should perform should have less overhead when cache is cold due it requires less accesses to shared resources.
    FIFO is a good canididate when you have very few cache entries and high hit rate.


    Expermients TODO: Check the impact on the cache hit performance if enclave makes modifications to other cache entries in the same cache.

*/

unsigned int
benchmark_memoize_fifo(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    printf("%zu %zu %zu\n", sizeof(struct function_cache_ctx), sizeof(struct cache_entry), sizeof(struct ecall_queue_item));
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "memoize_fifo", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 2, y = 1, counter = 0, res;
        const uint32_t tmp[] = { x, y };
        uint32_t hash = hcall_hash_words(tmp, 2, 0);
        struct memoize_config memo = { .hash = hash, .return_type = 'd', .manual_update = false, .eviction_policy = FIFO };
        s = __rdtscp(aux);
        HCALL_MEMOIZE(
            CONFIG(.function_id = hotcall_ecall_add_and_count, .memoize = &memo),
            VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(res != 3) printf("wrong answer %d\n", res);
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_memoize_lru(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "memoize_lru", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 2, y = 1, counter = 0, res;
        const uint32_t tmp[] = { x, y };
        uint32_t hash = hcall_hash_words(tmp, 2, 0);
        struct memoize_config memo = { .hash = hash, .return_type = 'd', .manual_update = false, .eviction_policy = LRU };
        s = __rdtscp(aux);
        HCALL_MEMOIZE(
            CONFIG(.function_id = hotcall_ecall_add_and_count, .memoize = &memo),
            VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(res != 3) printf("wrong answer %d\n", res);
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}


static int kkk = 0;
unsigned int
benchmark_memoize_modifications(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    // When a new value is inserted in the cache, the cache will be invalidated for the client thread and hence accessing the cache the next time becomes more expensive.
    // This demonstrates how the performance gains of memoization is reduced in the case of a busy cache. Even though the removed or inserted object is actually not the object
    // which a function is accessing.
    char file_path[512] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[512];
    create_file_name(file_name, "memoize_mod", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    int x = 2, y = 5, z = 10, counter = 0, counter1 = 0, res, res1 = 0;
    const uint32_t tmp1[] = { x, y }, tmp2[] = { x, z };
    uint32_t hash1 = hcall_hash_words(tmp1, 2, 0), hash2 = hcall_hash_words(tmp2, 2, 0);
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        struct memoize_config memo1 = { .hash = hash2, .return_type = 'd', .manual_update = false, .eviction_policy = FIFO };
        HCALL_MEMOIZE(
            CONFIG(
                .function_id = hotcall_ecall_add_and_count,
                .memoize = &memo1
            ),
            VAR(x, 'd'), VAR(z, 'd'), PTR(&counter), VAR(res, 'd')
        );

        if(res != x + z) {
            printf("1 wrong answer %d\n", res);
        }

        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);

        struct memoize_config memo2 = { .hash = hash1, .return_type = 'd', .manual_update = false, .eviction_policy = FIFO };
        //struct memoize_invalidate memo_inv1 = { .n_caches_to_invalidate = 1, .caches = {{ hotcall_ecall_get_addr, .type = CLEAR_CACHE }}};
        s = __rdtscp(aux);
        HCALL_MEMOIZE(
            CONFIG(
                .function_id = hotcall_ecall_add_and_count,
                .memoize = &memo2,
                .memoize_invalidate = NULL
            ),
            VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd')
        );
        e = __rdtscp(aux);

        struct memoize_invalidate memo_inv2 = { .n_caches_to_invalidate = 1, .caches = {{ hotcall_ecall_add_and_count, .type = HASH, .invalidate_element = { .hash = hash2 }}}};
        HCALL_SIMPLE(
            CONFIG(
                .function_id = hotcall_ecall_foo,
                .memoize = NULL,
                .memoize_invalidate = &memo_inv2
            )
        );
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(res != x + y) {
            printf("2 wrong answer %d\n", res);
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}


unsigned int
benchmark_memoize_off(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "memoize_off", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int _aux, *aux = &_aux; unsigned long long s, e;
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clearcache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        int x = 2, y = 1, counter = 0, res;
        s = __rdtscp(aux);
        const uint32_t tmp[] = { x, y };
        uint32_t hash = hcall_hash_words(tmp, 2, 0);
        HCALL_SIMPLE(
            CONFIG(.function_id = hotcall_ecall_add_and_count),
            VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd'));
        e = __rdtscp(aux);
        if(i >= warmup) {
            rounds[i - warmup] = e - s;
        }
        if(res != 3) printf("wrong answer %d\n", res);
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
