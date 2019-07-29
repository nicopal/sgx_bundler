#include "execute_function.h"

void
execute_function(const struct hotcall_config *hotcall_config, uint8_t function_id, int n_iters, int n_params, void *args[n_params][n_iters]) {
    void (*f)(unsigned int n_iters, unsigned int n_params, void *[n_params][n_iters]);
    f = hotcall_config->call_table[function_id];
    #ifdef SGX_DEBUG
    if(!f) {
        printf("unknown hotcall function %d.\n", function_id);
    }
    #endif
    f(n_iters, n_params, args);
}
