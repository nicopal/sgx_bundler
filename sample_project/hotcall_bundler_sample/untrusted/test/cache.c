#include "gtest/gtest.h"
#include "test.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"
#include "hotcall_cache.h"
#include "cache_trusted.h"
#include "hotcall-hash.h"

#include "sample.h"

#define MEMO_CACH_SIZE 10

TEST(cache, 1) {
    // Contract: Only the first call to SGX_add_and_count should triggert an ecall which will incremenet the counter by 1. The other 2 calls should hit in the function cache.

    int x = 1, y = 2, counter = 0, res = 0;

    hotcall_test_setup();

    const uint32_t tmp[] = { x, y };
    struct memoize_config memo = { .hash = hcall_hash_words(tmp, 2, 0), .return_type = 'd' };

    HCALL_MEMOIZE(CONFIG(.function_id = hotcall_ecall_add_and_count, .has_return = true, .memoize = &memo), VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd'));

    ASSERT_EQ(res, 3);
    ASSERT_EQ(counter, 1);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    HCALL(CONFIG(.function_id = hotcall_ecall_add_and_count, .has_return = true, .memoize = &memo), VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd'));

    ASSERT_EQ(res, 3);
    ASSERT_EQ(counter, 1);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    const uint32_t tmp1[] = { y, x };
    struct memoize_config memo1 = { .hash = hcall_hash_words(tmp1, 2, 0), .return_type = 'd' };

    HCALL(CONFIG(.function_id = hotcall_ecall_add_and_count, .has_return = true, .memoize = &memo1), VAR(y, 'd'), VAR(x, 'd'), PTR(&counter), VAR(res, 'd'));

    ASSERT_EQ(res, 3);
    ASSERT_EQ(counter, 2);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    struct shared_memory_ctx *sm_ctx = hotcall_test_get_context();
    hcall_hmap_clear(&sm_ctx->mem.functions[hotcall_ecall_add_and_count]->cache);

    hotcall_test_teardown();
}

TEST(cache, 2) {
    // Contract: The first iteration of the outer loop will result in a cache miss but all others will hit.

    int counter = 0, res = 0, x = 0;

    hotcall_test_setup();

    uint32_t tmp[2];
    for(int j = 0; j < 10; ++j) {
        for(int i = 0; i < MEMO_CACH_SIZE; ++i) {
            tmp[0] = 0, tmp[1] = i;
            struct memoize_config memo = { .hash = hcall_hash_words(tmp, 2, 0), 'd' };
            HCALL(CONFIG(.function_id = hotcall_ecall_add_and_count, .has_return = true, .memoize = &memo), VAR(x, 'd'), VAR(i, 'd'), PTR(&counter), VAR(res, 'd'));
            ASSERT_EQ(res, i);
        }
    }
    ASSERT_EQ(counter, MEMO_CACH_SIZE);

    struct shared_memory_ctx *sm_ctx = hotcall_test_get_context();
    hcall_hmap_clear(&sm_ctx->mem.functions[hotcall_ecall_add_and_count]->cache);

    hotcall_test_teardown();
}

TEST(cache, 3) {
    // Contract: all calls to SGX_add_and_count will miss due to the fact that the inner loop is larger than the size of the cache which will result
    // in that a value will always be evicted before we call the function with those values a second time.

    int counter = 0, res = 0, x = 0;

    hotcall_test_setup();

    uint32_t hash; uint32_t tmp[2];
    for(int j = 0; j < 10; ++j) {
        for(int i = 0; i < MEMO_CACH_SIZE + 1; ++i) {
            tmp[0] = 0, tmp[1] = i;
            struct memoize_config memo = { .hash = hcall_hash_words(tmp, 2, 0), 'd' };
            HCALL(CONFIG(
                    .function_id = hotcall_ecall_add_and_count, .has_return = true,
                    .memoize = &memo
                ),
                VAR(x, 'd'), VAR(i, 'd'), PTR(&counter), VAR(res, 'd')
            );
        }
    }
    ASSERT_EQ(counter, (MEMO_CACH_SIZE + 1) * 10);

    struct shared_memory_ctx *sm_ctx = hotcall_test_get_context();
    hcall_hmap_clear(&sm_ctx->mem.functions[hotcall_ecall_add_and_count]->cache);

    hotcall_test_teardown();
}

TEST(cache, 4) {
    // Contract: Counter should be 2 since the cache line which the second hcall should have hit is invalidated.

    int x = 1, y = 2, counter = 0, res = 0;

    hotcall_test_setup();

    const uint32_t tmp[] = { x, y };
    uint32_t hash = hcall_hash_words(tmp, 2, 0);
    struct memoize_config memo = { .hash = hash, .return_type = 'd' };
    HCALL(CONFIG(.function_id = hotcall_ecall_add_and_count, .has_return = true, .memoize = &memo), VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd'));

    ASSERT_EQ(res, 3);
    ASSERT_EQ(counter, 1);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    struct memoize_invalidate memo_inv1 = {
        .n_caches_to_invalidate = 1,
        .caches = {{ hotcall_ecall_add_and_count, .type = HASH, .invalidate_element = { .hash = hash }}}
    };
    HCALL(CONFIG(.function_id = hotcall_ecall_foo, .has_return = false, .memoize = NULL, .memoize_invalidate = &memo_inv1));


    HCALL(CONFIG(.function_id = hotcall_ecall_add_and_count, .has_return = true, .memoize = &memo), VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd'));

    ASSERT_EQ(res, 3);
    ASSERT_EQ(counter, 2);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);


    const uint32_t tmp1[] = { y, x };
    uint32_t hash1 = hcall_hash_words(tmp1, 2, 0);
    struct memoize_config memo1 = { .hash = hash1, .return_type = 'd' };
    struct memoize_invalidate memo_inv = { .n_caches_to_invalidate = 1, .caches = {{hotcall_ecall_add_and_count, .type = RETURN_VALUE, .invalidate_element = { .fmt = 'd' }}}};
    HCALL(
        CONFIG(
                .function_id = hotcall_ecall_add_and_count, .has_return = true,
                .memoize = &memo1,
                .memoize_invalidate = &memo_inv
        ),
        VAR(y, 'd'), VAR(x, 'd'), PTR(&counter), VAR(res, 'd')
    );
    ASSERT_EQ(res, 3);
    ASSERT_EQ(counter, 3);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    HCALL(
        CONFIG(.function_id = hotcall_ecall_add_and_count, .has_return = true, .memoize = &memo),
        VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd')
    );

    ASSERT_EQ(res, 3);
    ASSERT_EQ(counter, 4);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    struct shared_memory_ctx *sm_ctx = hotcall_test_get_context();
    hcall_hmap_clear(&sm_ctx->mem.functions[hotcall_ecall_add_and_count]->cache);

    hotcall_test_teardown();
}

TEST(cache, 5) {
    // Contract:

    int x = 1, y = 2, counter = 0, res = 0;
    struct shared_memory_ctx *sm_ctx = hotcall_test_get_context();

    hotcall_test_setup();

    const uint32_t tmp[] = { x, y };
    uint32_t hash = hcall_hash_words(tmp, 2, 0);
    struct memoize_config memo = { .hash = hash, .return_type = 'd' };
    struct memoize_invalidate memo_inv = {  .n_caches_to_invalidate = 1, .caches = {{ hotcall_ecall_add_and_count, .type = HASH, .invalidate_element = { .hash = hash }}}};
    HCALL(
        CONFIG(
            .function_id = hotcall_ecall_add_and_count,
            .has_return = true,
            .memoize = &memo,
            .memoize_invalidate = &memo_inv
        ), VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd')
    );

    HCALL(
        CONFIG(
            .function_id = hotcall_ecall_add_and_count,
            .has_return = true,
            .memoize = &memo,
        ), VAR(x, 'd'), VAR(y, 'd'), PTR(&counter), VAR(res, 'd')
    );

    ASSERT_EQ(res, 3);
    ASSERT_EQ(counter, 2);
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 2);

    hcall_hmap_clear(&sm_ctx->mem.functions[hotcall_ecall_add_and_count]->cache);

    hotcall_test_teardown();
}
