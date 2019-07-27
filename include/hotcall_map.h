#ifndef _H_HOTCALL_MAP
#define _H_HOTCALL_MAP

#include "hotcall_utils.h"
#include "hotcall_function.h"

#define _MAP(SM_CTX, ID, CONFIG, ...) \
    struct parameter CAT2(MAP_ARG_,ID)[] = { \
        __VA_ARGS__\
    }; \
    struct map_config CAT2(MAP_CONFIG_,ID) = CONFIG;\
    struct hotcall_map ID = { CAT2(MAP_ARG_,ID), &CAT2(MAP_CONFIG_,ID) };\
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_MAP, .call = { .ma = &ID }}; \
    CAT2(MAP_CONFIG_,ID).n_params = sizeof(CAT2(MAP_ARG_,ID))/sizeof(struct parameter);\
    bool CAT2(IS_FIRST_, ID) = hotcall_enqueue_item(SM_CTX, &CAT2(QUEUE_ITEM_, ID));\
    if(is_inside_chain(SM_CTX) && !CAT2(IS_FIRST_, ID)) {\
        chain_operators(SM_CTX,  CAT2(MAP_ARG_,ID));\
    }


#define MAP(CONFIG, ...) \
    _MAP(_sm_ctx, UNIQUE_ID, CONFIG, __VA_ARGS__)


struct map_config {
    const uint8_t function_id;
    unsigned int *n_iters;
    unsigned int n_params;
};
struct hotcall_map {
    struct parameter *params;
    struct map_config *config;
};

#endif
