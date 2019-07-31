#ifndef _H_HOTCALL_BENCHMARK_
#define _H_HOTCALL_BENCHMARK_

#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

#define DATA_PATH "./data/"
#define L3_CACHE_SIZE 1024 * 1024 * 4

void
clear_cache(char *buf, unsigned int buf_size);
void
create_test_folder(char *dir_path);
void
write_to_file(char *dir_path, char *file_name, unsigned int rounds[], unsigned int n_rounds);
void
create_file_name(char *name_buf, const char *name, bool cold_cache, unsigned int cache_clear_multiple);

int
cmpfunc (const void * a, const void * b);
void
benchmark(struct shared_memory_ctx *sm_ctx, unsigned int (*f_benchmark)(struct shared_memory_ctx *, unsigned int), unsigned int n_rounds, unsigned int n_iters);
void
benchmark_v2(struct shared_memory_ctx *sm_ctx, unsigned int (*f_benchmark)(struct shared_memory_ctx *, unsigned int, bool, unsigned int, char *), unsigned int n_rounds, unsigned int n_iters, bool cold_cache, unsigned int cache_clear_size, char *suffix);

unsigned int
benchmark_hotcall_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_vanilla_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_hotcall_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_vanilla_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_hotcall_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_vanilla_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_hotcall_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_vanilla_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_hotcall_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_vanilla_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_hotcall_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);
unsigned int
benchmark_vanilla_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_size, char *output_dir);

unsigned int
benchmark_variadic_function(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);

unsigned int
benchmark_if_naive(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);
unsigned int
benchmark_if_optimized(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);


unsigned int
benchmark_filter_naive(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);
unsigned int
benchmark_filter_optimized(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);


unsigned int
benchmark_map(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_filter(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);
unsigned int
benchmark_for_each(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_for(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);


unsigned int
benchmark_cache(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);


/* Hotcall bundle tests */

unsigned int
benchmark_hotcall_sz_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_sz_2(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_sz_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_sz_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_sz_25(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_sz_50(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_sz_100(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);

unsigned int
benchmark_hotcall_bundle_sz_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_bundle_sz_2(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_bundle_sz_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_bundle_sz_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_bundle_sz_25(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_bundle_sz_50(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_bundle_sz_100(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);

unsigned int
benchmark_hotcall_for_sz_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_sz_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_sz_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_sz_25(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_sz_50(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_sz_100(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);

unsigned int
benchmark_hotcall_for_each_sz_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_each_sz_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_each_sz_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_each_sz_25(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_each_sz_50(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_hotcall_for_each_sz_100(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);



unsigned int
benchmark_memoize_fifo(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_memoize_lru(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_memoize_modifications(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);
unsigned int
benchmark_memoize_off(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, bool cold_cache, unsigned int cache_clear_multiple, char *output_dir);


typedef unsigned long long ticks;
static __inline__ ticks start (void) {
  unsigned cycles_low, cycles_high;
  asm volatile ("CPUID\n\t"
		"RDTSC\n\t"
		"mov %%edx, %0\n\t"
		"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
		"%rax", "%rbx", "%rcx", "%rdx");
  return ((ticks)cycles_high << 32) | cycles_low;
}

static __inline__ ticks stop (void) {
  unsigned cycles_low, cycles_high;
  asm volatile("RDTSCP\n\t"
	       "mov %%edx, %0\n\t"
	       "mov %%eax, %1\n\t"
	       "CPUID\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax",
	       "%rbx", "%rcx", "%rdx");
  return ((ticks)cycles_high << 32) | cycles_low;
}


static ticks b_time;
static ticks e_time;

#define BEGIN \
    b_time = start();

#define CLOSE \
    e_time = stop();

#define SHOWTIME printf("%lu\n", e_time - b_time);

#define SHOWTIME5 \
    { \
        char buf[32]; \
        int n = sprintf(buf, "%lu\n", e_time - b_time); \
        n = write(5, buf, n); \
    }

#define GET_TIME e_time - b_time;


inline __attribute__((always_inline)) uint64_t clearcache(void *buf, size_t size) {
    uint64_t sum;
    size_t count = size / sizeof(uint64_t);
    volatile uint64_t *p = (volatile uint64_t *) buf;
    while (count--) {
        sum += *p;
        *p++ = 0;
    }

    asm volatile ("mfence");
    return sum;
}


#endif
