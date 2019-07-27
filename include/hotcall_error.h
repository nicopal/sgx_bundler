#ifndef _H_HOTCALL_ERROR
#define _H_HOTCALL_ERROR

#define _ERROR(SM_CTX, ID, ERROR) \
    struct error_config CAT2(ERROR_CONFIG_,ID) = { ERROR };\
    struct hotcall_error ID = { &CAT2(ERROR_CONFIG_,ID) };\
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_ERROR, .call = { .err = &ID }}; \
    hotcall_enqueue_item(SM_CTX, &CAT2(QUEUE_ITEM_, ID))

#define ERROR(ERROR) \
    _ERROR(_sm_ctx, UNIQUE_ID, ERROR)

#define RETURN \
    _ERROR(_sm_ctx, UNIQUE_ID, 0);

struct error_config {
    int error_code;
};

struct hotcall_error {
    struct error_config *config;
};

#endif
