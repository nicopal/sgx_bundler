#ifndef _H_HOTCALL_BENCHMARK_
#define _H_HOTCALL_BENCHMARK_

#include <sys/stat.h>
#include <unistd.h>

#define L1_CACHE_SIZE (1024 * (32 + 256 + 1024))
#define DATA_PATH "/home/jakob/ovs-sgx/hotcall_bundler/sample_project/hotcall_bundler_sample/untrusted/benchmark/data"
extern volatile long unsigned dummy[L1_CACHE_SIZE];

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

void
clear_cache();

static inline void
create_test_folder(char *dir_path) {
    struct stat st = { 0 };
    if(stat(dir_path, &st) == -1) {
        mkdir(dir_path, 0700);
    }

}

int
cmpfunc (const void * a, const void * b);
void
benchmark(struct shared_memory_ctx *sm_ctx, unsigned int (*f_benchmark)(struct shared_memory_ctx *, unsigned int), unsigned int n_rounds, unsigned int n_iters);
void
benchmark_v2(struct shared_memory_ctx *sm_ctx, unsigned int (*f_benchmark)(struct shared_memory_ctx *, unsigned int, unsigned int, bool), unsigned int n_rounds, unsigned int n_iters, bool cold_cache);

unsigned int
benchmark_hotcall_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_vanilla_0(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_hotcall_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_vanilla_1(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_hotcall_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_vanilla_3(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_hotcall_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_vanilla_5(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_hotcall_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_vanilla_10(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_hotcall_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);
unsigned int
benchmark_vanilla_15(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds, unsigned int round_nr, bool cold_cache);

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
benchmark_map(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);
unsigned int
benchmark_filter(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);
unsigned int
benchmark_for_each(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);
unsigned int
benchmark_for(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);


unsigned int
benchmark_cache(struct shared_memory_ctx *sm_ctx, unsigned int n_rounds);


#endif
