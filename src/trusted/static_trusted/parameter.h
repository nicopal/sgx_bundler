#ifndef _H_TRUSTED_HOTCALL_PARAMETER_
#define _H_TRUSTED_HOTCALL_PARAMETER_

#include "hotcall_function.h"
#include "hotcall_utils.h"
#include <string.h>

void
parse_function_arguments(const struct parameter *param, int n_params, int offset, void *args[n_params][1]);
void
parse_arguments(const struct parameter *param, unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters], int offset);

#endif
