#ifndef _H_TRUSTED_HOTCALL_EXECUTE_FUNCTION_
#define _H_TRUSTED_HOTCALL_EXECUTE_FUNCTION_

#include "hotcall_config.h"
#include <stdint.h>

void
execute_function(const struct hotcall_config *hotcall_config, uint8_t function_id, int n_iters, int n_params, void *args[n_params][n_iters]);

#endif
