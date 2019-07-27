#ifndef _H_HOTCALL_FOR
#define _H_HOTCALL_FOR

#include "hotcall_utils.h"
#include "hotcall_function.h"

#define _BEGIN_FOR(SM_CTX, ID, CONFIG) \
    struct for_config CAT2(FOR_CONFIG_,ID) = CONFIG; \
    struct hotcall_for_start ID = { &CAT2(FOR_CONFIG_,ID) }; \
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_FOR_BEGIN, .call = { .for_s = &ID }}; \
    hotcall_enqueue_item(SM_CTX, &CAT2(QUEUE_ITEM_, ID));\



#define BEGIN_FOR(CONFIG) \
    _BEGIN_FOR(_sm_ctx, UNIQUE_ID, CONFIG)


#define _END_FOR(SM_CTX, ID) \
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_FOR_END }; \
    hotcall_enqueue_item(_sm_ctx, &CAT2(QUEUE_ITEM_, ID));\
    calculate_loop_length(&(SM_CTX)->hcall, QUEUE_ITEM_TYPE_FOR_BEGIN);

#define END_FOR() _END_FOR(_sm_ctx, UNIQUE_ID)


struct for_config {
    unsigned int *n_iters;
    struct ecall_queue_item *loop_end;
    bool loop_in_process;
};

struct hotcall_for_start {
    struct for_config *config;
};

#endif
