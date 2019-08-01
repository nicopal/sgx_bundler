#include "for_each.h"
#include "predicate.h"
#include "execute_function.h"
#include "parameter.h"

void
hotcall_handle_for_each(struct ecall_queue_item *qi, const struct hotcall_config *hotcall_config, struct queue_context *queue_ctx, struct batch_status * batch_status) {
    struct hotcall_for_each *tor = qi->call.tor;

    unsigned int n_iters = *tor->config->n_iters;
    unsigned int n_params = tor->config->n_params;

    #ifdef SGX_DEBUG
    struct parameter *params_in = NULL;
    for(int i = 0; i < n_params; ++i) {
        if(tor->params[i].type == VECTOR_TYPE) {
            params_in = &tor->params[i];
            break;
        }
    }
    sgx_assert(params_in != NULL, "For each input parameters contains no vector. Undefined behaviour!");
    #endif

    void *args[n_params][n_iters];
    /*void *args[n_params];
    for(int i = 0; i < n_params; ++i) {
        switch(tor->params[i].type) {
            case POINTER_TYPE: args[i] = tor->params[i].value.pointer.arg; break;
            case VARIABLE_TYPE: args[i] = tor->params[i].value.variable.arg; break;
            case VECTOR_TYPE: args[i] = tor->params[i].value.vector.arg; break;
            default: SWITCH_DEFAULT_REACHED
        }
    }*/

    /*unsigned int step_size = 1;
    void **args[n_params]; struct parameter *param;
    for(int i = 0; i < n_params; ++i) {
        param = &tor->params[i];
        switch(param->type) {
            case POINTER_TYPE:
              args[i] = param->value.pointer.arg;
              if(param->value.pointer.dereference) args[i] = *(void **) args[i];
              if(param->value.pointer.member_offset) args[i] = (char *) args[i] + param->value.pointer.member_offset;
              break;
            case VARIABLE_TYPE:
              args[i] = param->value.variable.arg;
              if(param->value.variable.dereference) args[i] = *(void **) args[i];
              if(param->value.variable.member_offset) args[i] = (char *) args[i] + param->value.variable.member_offset;
              break;
            case VECTOR_TYPE:
              args[i] = param->value.vector.arg;
              if(param->value.vector.dereference) {
                for(int j = 0; j < n_iters; ++j) args[i][j] = *(void **) args[i][j];
              }
              if(param->value.vector.member_offset) {
                for(int j = 0; j < n_iters; ++j) args[i][j] = (char *) args[i][j] + param->value.vector.member_offset;
              }
              break;
            default: SWITCH_DEFAULT_REACHED
        }
    }*/

    parse_arguments(tor->params, n_iters, n_params, args, 0);
    execute_function(hotcall_config, tor->config->function_id, n_iters, n_params, args);

    /*void (*f)(unsigned int n_iters, unsigned int n_params, void *[n_params]);
    f = hotcall_config->call_table[tor->config->function_id];
    #ifdef SGX_DEBUG
    if(!f) {
        printf("unknown hotcall function %d.\n", tor->config->function_id);
    }
    #endif
    f(n_iters, n_params, args);*/
}
