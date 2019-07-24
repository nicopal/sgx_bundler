#ifndef HOTCALL_BUNDLER_T_H__
#define HOTCALL_BUNDLER_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "hotcall.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


int hotcall_bundler_start(struct shared_memory_ctx* sm_ctx);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
