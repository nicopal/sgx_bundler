#ifndef _H_FUNCTION_BUNDLER_
#define _H_FUNCTION_BUNDLER_

#include <stdbool.h>
#include <stdint.h>

#define HOTCALL_MAX_ARG 25

enum parameter_type { FUNCTION_TYPE, VARIABLE_TYPE, POINTER_TYPE, VECTOR_TYPE, STRUCT_TYPE };

#define CONFIG(...) ((struct hotcall_function_config)  { __VA_ARGS__ })
#define VAR(VAL, ...) (struct parameter) { .type = VARIABLE_TYPE, .value = { .variable = { .arg = &(VAL), __VA_ARGS__ }}}
#define PTR(VAL, ...) (struct parameter) { .type = POINTER_TYPE,  .value = { .pointer = { .arg = (void *) (VAL), __VA_ARGS__ }}}
#define VECTOR(...) (struct parameter) { .type = VECTOR_TYPE, .value = { .vector = { __VA_ARGS__ }}}
#define FUNC(...) (struct parameter) { .type = FUNCTION_TYPE, .value = { .function = { __VA_ARGS__ }}}
#define STRUCT(VAL, ...) (struct parameter) { .type = STRUCT_TYPE, .value = { .struct_ = { .arg = (VAL), __VA_ARGS__ }}}


#define _HCALL_BUNDLE(SM_CTX, ID, CONFIG, ...) \
    struct parameter CAT2(HCALL_ARGS_, ID)[] = { __VA_ARGS__ }; \
    struct hotcall_function_config CAT2(HCALL_CONFIG_, ID) = CONFIG; \
    struct hotcall_function ID = { CAT2(HCALL_ARGS_, ID), &CAT2(HCALL_CONFIG_, ID) };\
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_FUNCTION, .call = { .fc = &ID }};\
    CAT2(HCALL_CONFIG_, ID).n_params = sizeof(CAT2(HCALL_ARGS_, ID))/sizeof(struct parameter);\
    if(!(SM_CTX)->hcall.batch->queue) {\
        SM_CTX->hcall.batch->queue = &CAT2(QUEUE_ITEM_, ID);\
        SM_CTX->hcall.batch->top = &CAT2(QUEUE_ITEM_, ID);\
    } else {\
        CAT2(QUEUE_ITEM_, ID).prev = (SM_CTX)->hcall.batch->top;\
        SM_CTX->hcall.batch->top->next = &CAT2(QUEUE_ITEM_, ID);\
        SM_CTX->hcall.batch->top = &CAT2(QUEUE_ITEM_, ID);\
    }
#define _HCALL_MEMOIZE(SM_CTX, ID, CONFIG, ...) \
    struct parameter CAT2(HCALL_ARGS_, ID)[] = { __VA_ARGS__ }; \
    struct hotcall_function_config CAT2(HCALL_CONFIG_, ID) = CONFIG; \
    struct hotcall_function ID = { CAT2(HCALL_ARGS_, ID), &CAT2(HCALL_CONFIG_, ID) };\
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_FUNCTION, .call = { .fc = &ID }};\
    CAT2(HCALL_CONFIG_, ID).n_params = sizeof(CAT2(HCALL_ARGS_, ID))/sizeof(struct parameter);\
    if(CAT2(HCALL_CONFIG_, ID).memoize) { \
        struct function_cache_ctx *_f_ctx; \
        _f_ctx = (SM_CTX)->mem.functions[CAT2(HCALL_CONFIG_, ID).function_id]; \
        struct cache_entry *ce; \
        HCALL_HMAP_FOR_EACH_WITH_HASH(ce, hmap_node, CAT2(HCALL_CONFIG_, ID).memoize->hash, &_f_ctx->cache) { \
            hcall_list_remove(&ce->lru_list_node); \
            hcall_list_push_back(&_f_ctx->lru_list, &ce->lru_list_node); \
            switch(CAT2(HCALL_CONFIG_, ID).memoize->return_type) { \
                case 'd': \
                    *(int *) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ACCESS_FIELD(ce->type, INT_TYPE); \
                    break; \
                case 'b': \
                    *(bool *) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ACCESS_FIELD(ce->type, BOOL_TYPE); \
                    break; \
                case 'u': \
                    *(unsigned int *) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ACCESS_FIELD(ce->type, UNSIGNED_TYPE); \
                    break; \
                case 'p': \
                    *(void **) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ce->type.POINTER_TYPE; \
                    break;\
                case ui16: \
                    *(uint16_t *) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ce->type.UNSIGNED_TYPE_16; \
                    break; \
                default: SWITCH_DEFAULT_REACHED \
            } \
            goto CAT2(EXIT_, ID);\
        }\
    }\
    SM_CTX->hcall.ecall = &CAT2(QUEUE_ITEM_, ID);\
    make_hotcall(&(SM_CTX)->hcall);\
    CAT2(EXIT_, ID):

  #define _HCALL(SM_CTX, ID, CONFIG, ...) \
      struct parameter CAT2(HCALL_ARGS_, ID)[] = { __VA_ARGS__ }; \
      struct hotcall_function_config CAT2(HCALL_CONFIG_, ID) = CONFIG; \
      struct hotcall_function ID = { CAT2(HCALL_ARGS_, ID), &CAT2(HCALL_CONFIG_, ID) };\
      struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_FUNCTION, .call = { .fc = &ID }};\
      CAT2(HCALL_CONFIG_, ID).n_params = sizeof(CAT2(HCALL_ARGS_, ID))/sizeof(struct parameter);\
      if(CAT2(HCALL_CONFIG_, ID).memoize) { \
          struct function_cache_ctx *_f_ctx; \
          _f_ctx = (SM_CTX)->mem.functions[CAT2(HCALL_CONFIG_, ID).function_id]; \
          struct cache_entry *ce; \
          HCALL_HMAP_FOR_EACH_WITH_HASH(ce, hmap_node, CAT2(HCALL_CONFIG_, ID).memoize->hash, &_f_ctx->cache) { \
              hcall_list_remove(&ce->lru_list_node); \
              hcall_list_push_back(&_f_ctx->lru_list, &ce->lru_list_node); \
              switch(CAT2(HCALL_CONFIG_, ID).memoize->return_type) { \
                  case 'd': \
                      *(int *) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ACCESS_FIELD(ce->type, INT_TYPE); \
                      break; \
                  case 'b': \
                      *(bool *) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ACCESS_FIELD(ce->type, BOOL_TYPE); \
                      break; \
                  case 'u': \
                      *(unsigned int *) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ACCESS_FIELD(ce->type, UNSIGNED_TYPE); \
                      break; \
                  case 'p': \
                      *(void **) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ce->type.POINTER_TYPE; \
                      break;\
                  case ui16: \
                      *(uint16_t *) CAT2(HCALL_ARGS_, ID)[CAT2(HCALL_CONFIG_, ID).n_params - 1].value.variable.arg = ce->type.UNSIGNED_TYPE_16; \
                      break; \
                  default: SWITCH_DEFAULT_REACHED \
              } \
              goto CAT2(EXIT_, ID);\
          }\
      }\
      if(!(SM_CTX)->hcall.batch) { \
          SM_CTX->hcall.ecall = &CAT2(QUEUE_ITEM_, ID);\
          make_hotcall(&(SM_CTX)->hcall);\
      } else if(!(SM_CTX)->hcall.batch->queue) {\
          SM_CTX->hcall.batch->queue = &CAT2(QUEUE_ITEM_, ID);\
          SM_CTX->hcall.batch->top = &CAT2(QUEUE_ITEM_, ID);\
      } else {\
          CAT2(QUEUE_ITEM_, ID).prev = (SM_CTX)->hcall.batch->top;\
          SM_CTX->hcall.batch->top->next = &CAT2(QUEUE_ITEM_, ID);\
          SM_CTX->hcall.batch->top = &CAT2(QUEUE_ITEM_, ID);\
      }\
      CAT2(EXIT_, ID):


#define _HCALL_SIMPLE(SM_CTX, ID, CONFIG, ...) \
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_FUNCTION };\
    struct hotcall_function ID;\
    CAT2(QUEUE_ITEM_, ID).call.fc = &ID;\
    struct parameter CAT2(HCALL_ARGS_, ID)[] = { __VA_ARGS__ }; \
    struct hotcall_function_config CAT2(HCALL_CONFIG_, ID) = CONFIG; \
    ID.params = CAT2(HCALL_ARGS_, ID);\
    ID.config = &CAT2(HCALL_CONFIG_, ID);\
    CAT2(HCALL_CONFIG_, ID).n_params = sizeof(CAT2(HCALL_ARGS_, ID))/sizeof(struct parameter);\
    SM_CTX->hcall.ecall = &CAT2(QUEUE_ITEM_, ID);\
    make_hotcall(&(SM_CTX)->hcall);



#define HCALL(CONFIG, ...) \
    _HCALL(_sm_ctx, UNIQUE_ID, CONFIG, __VA_ARGS__)

#define HCALL_SIMPLE(CONFIG, ...) \
    _HCALL_SIMPLE(_sm_ctx, UNIQUE_ID, CONFIG, __VA_ARGS__)

#define HCALL_BUNDLE(CONFIG, ...) \
    _HCALL_BUNDLE(_sm_ctx, UNIQUE_ID, CONFIG, __VA_ARGS__)

#define HCALL_MEMOIZE(CONFIG, ...) \
    _HCALL_MEMOIZE(_sm_ctx, UNIQUE_ID, CONFIG, __VA_ARGS__)

struct variable_parameter {
    void *arg;
    char fmt;
    bool dereference;
    int member_offset;
};

struct function_parameter {
    uint8_t function_id;
    struct parameter *params;
    unsigned int n_params;
};

struct pointer_parameter {
    void *arg;
    char fmt;
    bool dereference;
    unsigned int member_offset;
};

struct struct_parameter {
    struct parameter *arg;
    unsigned int member_offset;
    unsigned int struct_size;
};

struct vector_parameter {
    void *arg;
    char fmt;
    unsigned int *len;
    bool dereference;
    int member_offset;
    unsigned int *vector_offset;
};

union parameter_types {
    struct variable_parameter variable;
    struct function_parameter function;
    struct pointer_parameter pointer;
    struct vector_parameter vector;
    struct struct_parameter struct_;
};

struct parameter {
    enum parameter_type type;
    union parameter_types value;
};


struct memoize_config {
    uint32_t hash;
    const char return_type;
    bool manual_update;
};

enum invalidate_type { RETURN_VALUE, HASH, CLEAR_CACHE, VALUE };

struct memoize_cache {
    uint8_t id;
    enum invalidate_type type;
    union {
        uint32_t hash;
        char fmt;
    } invalidate_element;
};

struct memoize_invalidate {
    uint8_t n_caches_to_invalidate;
    struct memoize_cache caches[4];
};

struct hotcall_function_config {
    const uint8_t function_id;
    struct memoize_config *memoize;
    struct memoize_invalidate *memoize_invalidate;
    uint8_t n_params;
};

struct hotcall_function {
    struct parameter *params;
    struct hotcall_function_config *config;
};

#endif
