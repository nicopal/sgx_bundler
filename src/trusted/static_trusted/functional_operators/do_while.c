#include "do_while.h"
#include "predicate.h"
#include "hotcall_function.h"
#include "parameter.h"


void
hotcall_handle_do_while(struct ecall_queue_item *qi, const struct hotcall_config *hotcall_config, struct queue_context *queue_ctx, struct batch_status * batch_status) {
    struct hotcall_do_while *dw = qi->call.dw;
    uint8_t function_id = dw->config->function_id;
    unsigned int n_params = dw->config->body_n_params;
    void *args[n_params][1];
    parse_function_arguments(dw->body_params, n_params, 0, args);
    while(true) {
        if(!evaluate_predicate(dw->config->postfix, dw->config->postfix_length, hotcall_config, 0)) {
            return;
        }
        execute_function(hotcall_config, function_id, 1, n_params, args);
    }
}
