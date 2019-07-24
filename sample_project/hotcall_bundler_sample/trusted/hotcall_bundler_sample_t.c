#include "hotcall_bundler_sample_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <errno.h>
#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


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

static sgx_status_t SGX_CDECL sgx_ecall_configure_hotcall(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_configure_hotcall();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_test_func_0_ret(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_test_func_0_ret_t));
	ms_ecall_test_func_0_ret_t* ms = SGX_CAST(ms_ecall_test_func_0_ret_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	ms->ms_retval = ecall_test_func_0_ret();


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_test_func_0(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	ecall_test_func_0();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_test_func_1(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_test_func_1_t));
	ms_ecall_test_func_1_t* ms = SGX_CAST(ms_ecall_test_func_1_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	ecall_test_func_1(ms->ms_a);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_test_func_3(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_test_func_3_t));
	ms_ecall_test_func_3_t* ms = SGX_CAST(ms_ecall_test_func_3_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	ecall_test_func_3(ms->ms_a, ms->ms_b, ms->ms_c);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_test_func_5(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_test_func_5_t));
	ms_ecall_test_func_5_t* ms = SGX_CAST(ms_ecall_test_func_5_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	ecall_test_func_5(ms->ms_a, ms->ms_b, ms->ms_c, ms->ms_d, ms->ms_e);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_test_func_10(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_test_func_10_t));
	ms_ecall_test_func_10_t* ms = SGX_CAST(ms_ecall_test_func_10_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	ecall_test_func_10(ms->ms_a, ms->ms_b, ms->ms_c, ms->ms_d, ms->ms_e, ms->ms_f, ms->ms_g, ms->ms_h, ms->ms_i, ms->ms_j);


	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_test_func_15(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_test_func_15_t));
	ms_ecall_test_func_15_t* ms = SGX_CAST(ms_ecall_test_func_15_t*, pms);
	sgx_status_t status = SGX_SUCCESS;


	ecall_test_func_15(ms->ms_a, ms->ms_b, ms->ms_c, ms->ms_d, ms->ms_e, ms->ms_f, ms->ms_g, ms->ms_h, ms->ms_i, ms->ms_j, ms->ms_k, ms->ms_l, ms->ms_m, ms->ms_n, ms->ms_o);


	return status;
}

static sgx_status_t SGX_CDECL sgx_hotcall_bundler_start(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_hotcall_bundler_start_t));
	ms_hotcall_bundler_start_t* ms = SGX_CAST(ms_hotcall_bundler_start_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	struct shared_memory_ctx* _tmp_sm_ctx = ms->ms_sm_ctx;


	ms->ms_retval = hotcall_bundler_start(_tmp_sm_ctx);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[9];
} g_ecall_table = {
	9,
	{
		{(void*)(uintptr_t)sgx_ecall_configure_hotcall, 0},
		{(void*)(uintptr_t)sgx_ecall_test_func_0_ret, 0},
		{(void*)(uintptr_t)sgx_ecall_test_func_0, 0},
		{(void*)(uintptr_t)sgx_ecall_test_func_1, 0},
		{(void*)(uintptr_t)sgx_ecall_test_func_3, 0},
		{(void*)(uintptr_t)sgx_ecall_test_func_5, 0},
		{(void*)(uintptr_t)sgx_ecall_test_func_10, 0},
		{(void*)(uintptr_t)sgx_ecall_test_func_15, 0},
		{(void*)(uintptr_t)sgx_hotcall_bundler_start, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[1][9];
} g_dyn_entry_table = {
	1,
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_print(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_t);
	void *__tmp = NULL;

	ocalloc_size += (str != NULL && sgx_is_within_enclave(str, _len_str)) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_t));

	if (str != NULL && sgx_is_within_enclave(str, _len_str)) {
		ms->ms_str = (char*)__tmp;
		__tmp = (void *)((size_t)__tmp + _len_str);
		memcpy((void*)ms->ms_str, str, _len_str);
	} else if (str == NULL) {
		ms->ms_str = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(0, ms);


	sgx_ocfree();
	return status;
}

