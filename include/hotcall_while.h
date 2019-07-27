#ifndef _H_HOTCALL_WHILE
#define _H_HOTCALL_WHILE

#include "hotcall_utils.h"
#include "hotcall_function.h"
#include "../src/untrusted/postfix_translator.h"

#define _END_WHILE(SM_CTX, ID) \
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_WHILE_END  }; \
    hotcall_enqueue_item(SM_CTX, &CAT2(QUEUE_ITEM_, ID));\
    calculate_loop_length(&(SM_CTX)->hcall, QUEUE_ITEM_TYPE_WHILE_BEGIN)

#define END_WHILE() _END_WHILE(_sm_ctx, UNIQUE_ID)

#define _BEGIN_WHILE(SM_CTX, ID, CONFIG, ...) \
    struct parameter CAT2(WHILE_ARG_,ID)[] = { \
        __VA_ARGS__\
    }; \
    struct while_config CAT2(WHILE_CONFIG_,ID) = CONFIG;\
    struct hotcall_while_start ID = { CAT2(WHILE_ARG_,ID), &CAT2(WHILE_CONFIG_,ID) };\
    CAT2(WHILE_CONFIG_,ID).n_params = sizeof(CAT2(WHILE_ARG_,ID))/sizeof(struct parameter);\
    struct postfix_item CAT2(POSTFIX_, ID)[strlen(CAT2(WHILE_CONFIG_, ID).predicate_fmt)];\
    CAT2(WHILE_CONFIG_,ID).postfix = CAT2(POSTFIX_, ID);\
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_WHILE_BEGIN, .call = { .while_s = &ID }}; \
    hotcall_enqueue_item(SM_CTX, &CAT2(QUEUE_ITEM_, ID));\
    CAT2(WHILE_CONFIG_, ID).postfix_length = to_postfix(CAT2(WHILE_CONFIG_, ID).predicate_fmt, ID.params, CAT2(WHILE_CONFIG_, ID).postfix);

#define BEGIN_WHILE(CONFIG, ...) \
    _BEGIN_WHILE(_sm_ctx, UNIQUE_ID, CONFIG, __VA_ARGS__)

struct while_config {
    const char *predicate_fmt;
    bool iter_vectors;
    bool loop_in_process;
    struct ecall_queue_item *loop_end;
    struct ecall_queue_item *loop_start;
    unsigned int n_params;
    struct postfix_item *postfix;
    unsigned int postfix_length;
};

struct hotcall_while_start {
    struct parameter *params;
    struct while_config *config;
};

#endif
