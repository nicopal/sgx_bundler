#include "benchmark.h"
#include "hotcall-bundler-untrusted.h"
#include "functions.h"

unsigned int
benchmark_map(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "map", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int n_iters = 10000;
    int xs[n_iters] = { 0 }, ys[n_iters] = { 0 };
    for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        BEGIN
        BUNDLE_BEGIN();
        MAP(((struct map_config) {
                .function_id = hotcall_ecall_plus_one_ret,
                .n_iters = &n_iters
            }),
            VECTOR(xs, 'd'),
            VECTOR(ys, 'd')
        );
        BUNDLE_END();
        CLOSE
        if(i >= warmup) {
            rounds[i - warmup] = GET_TIME
        }
    }
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}

unsigned int
benchmark_for_each(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir) {
    char file_path[256] = DATA_PATH;
    strcat(file_path, output_dir);
    char file_name[256];
    create_file_name(file_name, "map", cold_cache, cache_clear_multiple);
    printf("Dir: %s, File: %s\n", file_path, file_name);
    char *buf = (char *) malloc(cache_clear_multiple * L3_CACHE_SIZE);
    unsigned int warmup = n_rounds/5, rounds[n_rounds];
    unsigned int n_iters = 50;


/*
struct A xs[n_iters] = { 0 };
struct A *xs_ptr[n_iters] = { 0 };
for(int j = 0; j < n_iters; ++j) xs_ptr[j] = &xs[j];

      cache hit test
      struct A {
        unsigned int x;
      }__attribute__((aligned(64)));

      struct A {
        unsigned int x;
      };

      BEGIN
      BUNDLE_BEGIN();
      FOR_EACH(((struct for_each_config) {
              .function_id = hotcall_ecall_plus_one,
              .n_iters = &n_iters
          }),
          VECTOR(xs_ptr, 'p', &n_iters, .dereference = true, .member_offset = offsetof(struct A, x))
      );
      BUNDLE_END();

      */

      for(int i = 0; i < (n_rounds + warmup); ++i) {
          BEGIN

          int xs[n_iters] = { 5,5,5,5,5 }, ys[n_iters]; unsigned int out_length = 0;
          int zs[n_iters] = { 0 }, y = 3;



          /*FOR_EACH(((struct for_each_config) {
                  .function_id = hotcall_ecall_foo,
                  .n_iters = &n_iters
                })
          );*/


            /*struct parameter function_parameter[] = {
                VECTOR(xs, 'd', &n_iters),
                VECTOR(zs, 'd', &n_iters)
            };

          FILTER(
              ((struct filter_config) { .predicate_fmt = "b" }),
              FUNC(.function_id = hotcall_ecall_greater_than_two, .params = function_parameter, .n_params = 2),
              VECTOR(ys, 'd', &out_length)
          );*/
          BUNDLE_BEGIN();
          MAP(
            ((struct map_config) { .function_id = hotcall_ecall_plus_one_ret, .n_iters = &n_iters }),
            VECTOR(xs, 'd'),
            VECTOR(ys, 'd')
          );
          FILTER(
              ((struct filter_config) { .predicate_fmt = "d>d" }),
              VECTOR(ys, 'd', &n_iters), VAR(y, 'd'), VECTOR(zs, 'd', &out_length)
          );
          /*BUNDLE_END();
          for(int j = 0; j < n_iters; ++j) {
            if(ys[j] > y) zs[out_length++] = ys[j];
          }
          BUNDLE_BEGIN();*/
          FOR_EACH(((struct for_each_config) {
                  .function_id = hotcall_ecall_foo,
                  .n_iters = &out_length
                })
          );
          BUNDLE_END();

          if(out_length != 5) printf("out length wrong %d\n", out_length);
          for(int j = 0; j < out_length; ++j) {
            if(zs[j] != 6) printf("elem\n");
          }
          /*FILTER(
              ((struct filter_config) { .predicate_fmt = "d>d" }),
              VECTOR(ys, 'd', &n_iters), VAR(y, 'd'), VECTOR(zs, 'd', &out_length)
          );*/


        /*  BEGIN_FOR(((struct for_config) {
              .n_iters = &n_iters
          }));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
              HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
          END_FOR();

          BUNDLE_END();*/

          /*for(int i = 0; i < 50; ++i) {
            HCALL_SIMPLE(CONFIG(.function_id = hotcall_ecall_foo));
          }*/

          /*BUNDLE_BEGIN();

          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));

          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));

          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));

          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));

          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));
          HCALL_BUNDLE(CONFIG(.function_id = hotcall_ecall_foo));

          //}
          BUNDLE_END();*/
          CLOSE
          if(i >= warmup) {
              rounds[i - warmup] = GET_TIME
          }
      }

    /*for(int i = 0; i < (n_rounds + warmup); ++i) {
        if(cold_cache && i >= warmup) clear_cache(buf, cache_clear_multiple * L3_CACHE_SIZE);
        //int __attribute ((aligned(64))) xs[n_iters] = { 0 };
        int __attribute ((aligned(64))) xs[n_iters] = { 0 };
        bool ys[n_iters];
        BEGIN
        BUNDLE_BEGIN();
        FOR_EACH(((struct for_each_config) {
                .function_id = hotcall_ecall_foo,
                .n_iters = &n_iters
            })//, VAR(n_iters, 'd')//, VECTOR(ys, 'd')
        );
        BUNDLE_END();
        CLOSE
        if(i >= warmup) {
            rounds[i - warmup] = GET_TIME
        }
        for(int i = 0; i < n_iters; ++i) {
            //if(xs[i] != 1) printf("wrong answer %d\n", ys[i]);
        }
    }*/
    write_to_file(file_path, file_name, rounds, n_rounds);
    qsort(rounds, n_rounds, sizeof(unsigned int), cmpfunc);
    return rounds[n_rounds / 2];
}
