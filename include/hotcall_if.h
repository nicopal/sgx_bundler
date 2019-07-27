#ifndef _H_HOTCALL_IF
#define _H_HOTCALL_IF

#include "hotcall_utils.h"
#include "hotcall_function.h"

#define PASTE(X, Y) X ## Y

#define _IF(SM_CTX, ID, CONFIG, ...) \
    struct parameter CAT2(IF_ARG_, ID)[] = { __VA_ARGS__ }; \
    struct if_config CAT2(IF_CONFIG_, ID) = CONFIG; \
    struct postfix_item CAT2(POSTFIX_, ID)[16];\
    struct hotcall_if ID = { .params = CAT2(IF_ARG_, ID), .config = &CAT2(IF_CONFIG_, ID) };\
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { .type = QUEUE_ITEM_TYPE_IF, .call = { .tif = &ID }}; \
    CAT2(IF_CONFIG_, ID).postfix = CAT2(POSTFIX_, ID); \
    CAT2(IF_CONFIG_, ID).postfix_length = to_postfix(CAT2(IF_CONFIG_, ID).predicate_fmt, CAT2(QUEUE_ITEM_, ID).call.tif->params, CAT2(IF_CONFIG_, ID).postfix);\
    if(!(SM_CTX)->hcall.batch->queue) {\
        SM_CTX->hcall.batch->queue = SM_CTX->hcall.batch->top = &CAT2(QUEUE_ITEM_, ID);\
    } else {\
        CAT2(QUEUE_ITEM_, ID).prev = (SM_CTX)->hcall.batch->top;\
        SM_CTX->hcall.batch->top->next = &CAT2(QUEUE_ITEM_, ID);\
        SM_CTX->hcall.batch->top = &CAT2(QUEUE_ITEM_, ID);\
    }

#define IF(CONFIG, ...) \
    _IF(_sm_ctx, UNIQUE_ID, CONFIG, __VA_ARGS__);

#define THEN
#define _ELSE(SM_CTX, ID) \
    struct if_else_config CAT2(IF_ELSE_CONFIG_, ID);\
    struct hotcall_if_else ID = { &CAT2(IF_ELSE_CONFIG_, ID) };\
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_IF_ELSE, .call = { .tife = &ID }}; \
    hotcall_enqueue_item(SM_CTX, &CAT2(QUEUE_ITEM_, ID));

#define ELSE _ELSE(_sm_ctx, UNIQUE_ID)

#define _END(SM_CTX, ID) \
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_IF_END }; \
    hotcall_enqueue_item(SM_CTX, &CAT2(QUEUE_ITEM_, ID));\
    calculate_if_body_length(SM_CTX);

#define END _END(_sm_ctx, UNIQUE_ID)

#define INIT_IF_CONF(FMT, RETURN_IF_FALSE) ((struct if_config) { FMT, RETURN_IF_FALSE })


struct postfix_item {
        char ch;
        struct parameter *elem;
};

struct if_config {
    const char *predicate_fmt;
    const bool return_if_false;
    struct ecall_queue_item *if_end;
    struct ecall_queue_item *else_branch;
    struct ecall_queue_item *then_branch;
    struct postfix_item *postfix;
    unsigned int postfix_length;
};

struct if_else_config {
    struct ecall_queue_item *if_end;
};

struct hotcall_if {
    struct parameter *params;
    struct if_config *config;
};

struct hotcall_if_else {
    struct if_else_config *config;
};

#endif
