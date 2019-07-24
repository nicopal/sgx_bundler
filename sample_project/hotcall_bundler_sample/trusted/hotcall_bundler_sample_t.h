#ifndef HOTCALL_BUNDLER_SAMPLE_T_H__
#define HOTCALL_BUNDLER_SAMPLE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "stdbool.h"
#include "hotcall.h"
#include "ecalls.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


void ecall_configure_hotcall();
int ecall_test_func_0_ret();
void ecall_test_func_0();
void ecall_test_func_1(int a);
void ecall_test_func_3(int a, int b, int c);
void ecall_test_func_5(int a, int b, int c, int d, int e);
void ecall_test_func_10(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
void ecall_test_func_15(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o);
int hotcall_bundler_start(struct shared_memory_ctx* sm_ctx);

sgx_status_t SGX_CDECL ocall_print(const char* str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
