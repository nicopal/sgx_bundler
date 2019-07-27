#include "hotcall_bundler_u.h"
#include "hotcall-bundler-untrusted.h"
#include <pthread.h>
#include <assert.h>
#include "postfix_translator.h"

struct shared_memory_ctx *_sm_ctx;
static sgx_enclave_id_t global_eid;
struct hotcall_config * _hotcall_config;

void *
start_enclave_thread(void * vargp){
    printf("start_enclave_thread\n");
    int ecall_return;
    hotcall_bundler_start(global_eid, &ecall_return, _sm_ctx);
    if (ecall_return == 0) {
        printf("Application ran with success\n");
    } else {
        printf("Application failed %d \n", ecall_return);
    }
}

void
hotcall_init(struct shared_memory_ctx *ctx, sgx_enclave_id_t eid) {
    ctx->hcall.is_inside_chain = false;

    // Inititalize function memoize caches.
    struct function_cache_ctx *mem_ctx;
    struct cache_entry *entries;
    unsigned int cache_sz;
    for(int i = 0; i < ctx->mem.max_n_function_caches; ++i) {
        cache_sz = ctx->mem.function_cache_size[i];
        if(cache_sz == 0) continue;
        mem_ctx = malloc(sizeof(struct function_cache_ctx));
        entries = malloc(sizeof(struct cache_entry) * cache_sz);
        hcall_list_init(&mem_ctx->lru_list);
        for(int j = 0; j < cache_sz; ++j) {
            hcall_list_insert(&mem_ctx->lru_list, &entries[j].lru_list_node);
        }
        hcall_hmap_init(&mem_ctx->cache);
        hcall_hmap_reserve(&mem_ctx->cache, cache_sz);
        hcall_hmap_init(&mem_ctx->val_cache);
        hcall_hmap_reserve(&mem_ctx->val_cache, cache_sz);
        ctx->mem.functions[i] = mem_ctx;
    }

    global_eid = eid;
    _sm_ctx = ctx;
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, start_enclave_thread, NULL);
}

void
hotcall_destroy(struct shared_memory_ctx *sm_ctx) {
    struct ecall_queue_item item;
    item.type = QUEUE_ITEM_TYPE_DESTROY;
    sm_ctx->hcall.ecall = &item;
    hotcall_bundle_flush(sm_ctx);
    sm_ctx->hcall.ecall = NULL;
}

bool
hotcall_enqueue_item(struct shared_memory_ctx *sm_ctx, struct ecall_queue_item *item) {
    bool is_first_element = false;
    if(!sm_ctx->hcall.batch->queue) {
        sm_ctx->hcall.batch->queue = sm_ctx->hcall.batch->top = item;
        is_first_element = true;
    }
    else {
        item->prev = sm_ctx->hcall.batch->top;
        sm_ctx->hcall.batch->top->next = item;
        sm_ctx->hcall.batch->top = item;
    }
    return is_first_element;
}
