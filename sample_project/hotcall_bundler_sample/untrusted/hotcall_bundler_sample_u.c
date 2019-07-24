#include "hotcall_bundler_sample_u.h"
#include <errno.h>

typedef struct ms_ecall_test_func_0_ret_t {
	int ms_retval;
} ms_ecall_test_func_0_ret_t;

typedef struct ms_ecall_test_func_1_t {
	int ms_a;
} ms_ecall_test_func_1_t;

typedef struct ms_ecall_test_func_3_t {
	int ms_a;
	int ms_b;
	int ms_c;
} ms_ecall_test_func_3_t;

typedef struct ms_ecall_test_func_5_t {
	int ms_a;
	int ms_b;
	int ms_c;
	int ms_d;
	int ms_e;
} ms_ecall_test_func_5_t;

typedef struct ms_ecall_test_func_10_t {
	int ms_a;
	int ms_b;
	int ms_c;
	int ms_d;
	int ms_e;
	int ms_f;
	int ms_g;
	int ms_h;
	int ms_i;
	int ms_j;
} ms_ecall_test_func_10_t;

typedef struct ms_ecall_test_func_15_t {
	int ms_a;
	int ms_b;
	int ms_c;
	int ms_d;
	int ms_e;
	int ms_f;
	int ms_g;
	int ms_h;
	int ms_i;
	int ms_j;
	int ms_k;
	int ms_l;
	int ms_m;
	int ms_n;
	int ms_o;
} ms_ecall_test_func_15_t;

typedef struct ms_hotcall_bundler_start_t {
	int ms_retval;
	struct shared_memory_ctx* ms_sm_ctx;
} ms_hotcall_bundler_start_t;

typedef struct ms_ocall_print_t {
	char* ms_str;
} ms_ocall_print_t;

static sgx_status_t SGX_CDECL hotcall_bundler_sample_ocall_print(void* pms)
{
	ms_ocall_print_t* ms = SGX_CAST(ms_ocall_print_t*, pms);
	ocall_print((const char*)ms->ms_str);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[1];
} ocall_table_hotcall_bundler_sample = {
	1,
	{
		(void*)hotcall_bundler_sample_ocall_print,
	}
};
sgx_status_t ecall_configure_hotcall(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 0, &ocall_table_hotcall_bundler_sample, NULL);
	return status;
}

sgx_status_t ecall_test_func_0_ret(sgx_enclave_id_t eid, int* retval)
{
	sgx_status_t status;
	ms_ecall_test_func_0_ret_t ms;
	status = sgx_ecall(eid, 1, &ocall_table_hotcall_bundler_sample, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

sgx_status_t ecall_test_func_0(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 2, &ocall_table_hotcall_bundler_sample, NULL);
	return status;
}

sgx_status_t ecall_test_func_1(sgx_enclave_id_t eid, int a)
{
	sgx_status_t status;
	ms_ecall_test_func_1_t ms;
	ms.ms_a = a;
	status = sgx_ecall(eid, 3, &ocall_table_hotcall_bundler_sample, &ms);
	return status;
}

sgx_status_t ecall_test_func_3(sgx_enclave_id_t eid, int a, int b, int c)
{
	sgx_status_t status;
	ms_ecall_test_func_3_t ms;
	ms.ms_a = a;
	ms.ms_b = b;
	ms.ms_c = c;
	status = sgx_ecall(eid, 4, &ocall_table_hotcall_bundler_sample, &ms);
	return status;
}

sgx_status_t ecall_test_func_5(sgx_enclave_id_t eid, int a, int b, int c, int d, int e)
{
	sgx_status_t status;
	ms_ecall_test_func_5_t ms;
	ms.ms_a = a;
	ms.ms_b = b;
	ms.ms_c = c;
	ms.ms_d = d;
	ms.ms_e = e;
	status = sgx_ecall(eid, 5, &ocall_table_hotcall_bundler_sample, &ms);
	return status;
}

sgx_status_t ecall_test_func_10(sgx_enclave_id_t eid, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
{
	sgx_status_t status;
	ms_ecall_test_func_10_t ms;
	ms.ms_a = a;
	ms.ms_b = b;
	ms.ms_c = c;
	ms.ms_d = d;
	ms.ms_e = e;
	ms.ms_f = f;
	ms.ms_g = g;
	ms.ms_h = h;
	ms.ms_i = i;
	ms.ms_j = j;
	status = sgx_ecall(eid, 6, &ocall_table_hotcall_bundler_sample, &ms);
	return status;
}

sgx_status_t ecall_test_func_15(sgx_enclave_id_t eid, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o)
{
	sgx_status_t status;
	ms_ecall_test_func_15_t ms;
	ms.ms_a = a;
	ms.ms_b = b;
	ms.ms_c = c;
	ms.ms_d = d;
	ms.ms_e = e;
	ms.ms_f = f;
	ms.ms_g = g;
	ms.ms_h = h;
	ms.ms_i = i;
	ms.ms_j = j;
	ms.ms_k = k;
	ms.ms_l = l;
	ms.ms_m = m;
	ms.ms_n = n;
	ms.ms_o = o;
	status = sgx_ecall(eid, 7, &ocall_table_hotcall_bundler_sample, &ms);
	return status;
}

sgx_status_t hotcall_bundler_start(sgx_enclave_id_t eid, int* retval, struct shared_memory_ctx* sm_ctx)
{
	sgx_status_t status;
	ms_hotcall_bundler_start_t ms;
	ms.ms_sm_ctx = sm_ctx;
	status = sgx_ecall(eid, 8, &ocall_table_hotcall_bundler_sample, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

