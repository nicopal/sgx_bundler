#include <string.h>
#include <assert.h>

#include <unistd.h>
#include <pwd.h>
#include <libgen.h>
#include <stdlib.h>

#include <sgx_urts.h>
#include "sample.h"

#include "hotcall_bundler_sample_u.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include "examples.h"
#include <gtest/gtest.h>
#include "test/test.h"
#include "benchmark/benchmark.h"


sgx_enclave_id_t global_eid = 0;

static struct shared_memory_ctx sm_ctx;

/* OCall functions */
void ocall_print(const char *str)
{
    printf("%s", str);
}

int initialize_enclave(void)
{
    sgx_launch_token_t token = {0};
    int token_updated;
    sgx_misc_attribute_t attr;
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = sgx_create_enclave(HOTCALL_BUNDLER_SAMPLE_FILENAME, SGX_DEBUG_FLAG, &token, &token_updated, &global_eid, &attr);
    if (ret != SGX_SUCCESS) {
        printf("Failed to initialize enclave.\n");
        return -1;
    }
    return 0;
}

#define ROUNDS 1

/* Application entry */
int SGX_CDECL main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    /* Initialize the enclave */
    if(initialize_enclave() < 0){
        printf("failed to initilize enclave.\n");
        return -1;
    }

    sm_ctx.mem.max_n_function_caches = 256;
    sm_ctx.mem.function_cache_size[hotcall_ecall_add_and_count] = 10;
    sm_ctx.mem.function_cache_size[hotcall_ecall_get_addr] = 5;

    if(argc > 1 && !strcmp(argv[1], "-t")) {
        printf("Running test...\n");
        return hotcall_run_tests(&sm_ctx);
    }

    if(argc < 2 || strcmp(argv[1], "-b")) {
        printf("Please specify if you want to run tests(-t) or benchmark(-b).\n");
        return 0;
    }

    char *output_path = (char *) argv[2];
    char *benchmark_name = (char *) argv[3];
    unsigned int n_iters = atoi(argv[4]);
    bool cold_cache = argc > 5 && !strcmp(argv[5], "-cold") ? true : false;
    int cache_clear_size_multiple = argc > 6 ? atoi(argv[6]) : 1;
    printf("multiple %d\n", cache_clear_size_multiple);

    printf("Running benchmark %s.\n", benchmark_name);

    if(strstr(benchmark_name, "vanilla") == NULL) {
        ecall_configure_hotcall(global_eid);
        hotcall_init(&sm_ctx, global_eid);
    }

    if(!strcmp(benchmark_name, "map")) {
        benchmark_v2(&sm_ctx, benchmark_map, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_0")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_0, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "vanilla_0")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_0, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_1")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_1, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "vanilla_1")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_1, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_3")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_3, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "vanilla_3")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_3, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_5")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_5, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "vanilla_5")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_5, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_10")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_10, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "vanilla_10")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_10, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_15")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_15, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "vanilla_15")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_15, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_sz_1")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_sz_1, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_sz_2")) {
       benchmark_v2(&sm_ctx, benchmark_hotcall_sz_2, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_sz_5")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_sz_5, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_sz_10")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_sz_10, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_sz_25")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_sz_25, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_sz_50")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_sz_50, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_sz_100")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_sz_100, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_bundle_sz_1")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_bundle_sz_1, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_bundle_sz_2")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_bundle_sz_2, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_bundle_sz_5")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_bundle_sz_5, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_bundle_sz_10")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_bundle_sz_10, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_bundle_sz_25")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_bundle_sz_25, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_bundle_sz_50")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_bundle_sz_50, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_bundle_sz_100")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_bundle_sz_100, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_sz_1")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_sz_1, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_sz_2")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_sz_2, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_sz_5")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_sz_5, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_sz_10")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_sz_10, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_sz_25")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_sz_25, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_sz_50")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_sz_50, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_sz_100")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_sz_100, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_each_sz_1")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_each_sz_1, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_each_sz_2")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_each_sz_2, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_each_sz_5")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_each_sz_5, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_each_sz_10")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_each_sz_10, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_each_sz_25")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_each_sz_25, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_each_sz_50")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_each_sz_50, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_for_each_sz_100")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_for_each_sz_100, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "memoize_lru")) {
        benchmark_v2(&sm_ctx, benchmark_memoize_lru, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "memoize_fifo")) {
        benchmark_v2(&sm_ctx, benchmark_memoize_fifo, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "memoize_off")) {
        benchmark_v2(&sm_ctx, benchmark_memoize_off, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "memoize_mod")) {
        benchmark_v2(&sm_ctx, benchmark_memoize_modifications, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_branch_true")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_branch_true, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_branch_true_naive")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_branch_true_naive, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_branch_false")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_branch_false, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_branch_false_naive")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_branch_false_naive, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_branch_true_loop")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_branch_true_loop, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_branch_true_naive_loop")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_branch_true_naive_loop, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_branch_false_loop")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_branch_false_loop, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_branch_false_naive_loop")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_branch_false_naive_loop, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_loop_1")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_loop_1, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_loop_3")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_loop_3, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_loop_5")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_loop_5, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_loop_10")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_loop_10, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_iterator_1")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_iterator_1, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_iterator_3")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_iterator_3, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_iterator_5")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_iterator_5, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_iterator_10")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_iterator_10, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_iterator_filter")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_iterator_filter, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    } else if(!strcmp(benchmark_name, "hotcall_loop_filter")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_loop_filter, n_iters, ROUNDS, cold_cache, cache_clear_size_multiple, output_path);
    }



    if(strstr(benchmark_name, "vanilla") == NULL) {
        hotcall_destroy(&sm_ctx);
    }

  return 0;
}
