#ifndef HOTCALL_BUNDLER_SAMPLE_U_H__
#define HOTCALL_BUNDLER_SAMPLE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */

#include "stdbool.h"
#include "hotcall.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print, (const char* str));

sgx_status_t ecall_configure_hotcall(sgx_enclave_id_t eid);
sgx_status_t ecall_test_func_0_ret(sgx_enclave_id_t eid, int* retval);
sgx_status_t ecall_test_func_0(sgx_enclave_id_t eid);
sgx_status_t ecall_test_func_1(sgx_enclave_id_t eid, int a);
sgx_status_t ecall_test_func_3(sgx_enclave_id_t eid, int a, int b, int c);
sgx_status_t ecall_test_func_5(sgx_enclave_id_t eid, int a, int b, int c, int d, int e);
sgx_status_t ecall_test_func_10(sgx_enclave_id_t eid, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
sgx_status_t ecall_test_func_15(sgx_enclave_id_t eid, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o);
sgx_status_t hotcall_bundler_start(sgx_enclave_id_t eid, int* retval, struct shared_memory_ctx* sm_ctx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
