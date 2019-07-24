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
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    ret = sgx_create_enclave(HOTCALL_BUNDLER_SAMPLE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
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


    if(argc < 2) {
        printf("No benchmark specified.\n");
        return 0;
    }

    char *benchmark_name = (char *) argv[1];

    printf("Running benchmark %s.\n", benchmark_name);

    if(strstr(benchmark_name, "hotcall") != NULL) {
        ecall_configure_hotcall(global_eid);
        hotcall_init(&sm_ctx, global_eid);
    }

    unsigned int n_iters = atoi(argv[2]);
    bool cold_cache = argc > 3 && !strcmp(argv[3], "-cold") ? true : false;

    if(!strcmp(benchmark_name, "map")) {
        benchmark(&sm_ctx, benchmark_map, n_iters, ROUNDS);
    } else if(!strcmp(benchmark_name, "hotcall_0")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_0, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "vanilla_0")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_0, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "hotcall_1")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_1, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "vanilla_1")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_1, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "hotcall_3")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_3, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "vanilla_3")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_3, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "hotcall_5")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_5, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "vanilla_5")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_5, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "hotcall_10")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_10, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "vanilla_10")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_10, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "hotcall_15")) {
        benchmark_v2(&sm_ctx, benchmark_hotcall_15, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "vanilla_15")) {
        benchmark_v2(&sm_ctx, benchmark_vanilla_15, n_iters, ROUNDS, cold_cache);
    } else if(!strcmp(benchmark_name, "for_each")) {
        benchmark(&sm_ctx, benchmark_for_each, n_iters, ROUNDS);
    }

    if(strstr(benchmark_name, "hotcall") != NULL) {
        hotcall_destroy(&sm_ctx);
    }

  return 0;
}
