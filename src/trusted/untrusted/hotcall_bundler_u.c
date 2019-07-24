#include "hotcall_bundler_u.h"
#include <errno.h>

typedef struct ms_hotcall_bundler_start_t {
	int ms_retval;
	struct shared_memory_ctx* ms_sm_ctx;
} ms_hotcall_bundler_start_t;

static const struct {
	size_t nr_ocall;
	void * table[1];
} ocall_table_hotcall_bundler = {
	0,
	{ NULL },
};
sgx_status_t hotcall_bundler_start(sgx_enclave_id_t eid, int* retval, struct shared_memory_ctx* sm_ctx)
{
	sgx_status_t status;
	ms_hotcall_bundler_start_t ms;
	ms.ms_sm_ctx = sm_ctx;
	status = sgx_ecall(eid, 0, &ocall_table_hotcall_bundler, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

