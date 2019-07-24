#ifndef _H_ECALLS_
#define _H_ECALLS_

#include <stdbool.h>

struct A { int x; int y; };

bool
ecall_always_true();
bool
ecall_always_false();
void
ecall_foo();
void
ecall_bar();
void
ecall_plus_one(int *x);
int
ecall_plus_one_ret(int x);
bool
ecall_greater_than_two(int *x);
bool
ecall_greater_than_y(int *x, int y);
void
ecall_plus_plus(int *x, int *y);
int
ecall_plus(int x, int y);
void
ecall_plus_y(int *x, int y);
void
ecall_plus_y_v2(int x, int *y);
bool
ecall_revert(bool x);
void
ecall_zero(int *x);
void
ecall_change_ptr_to_ptr(int **p2p, int *p);
void
ecall_offset_of(void **ptr, int offset);
void *
ecall_offset_of_ret(void *ptr, unsigned int offset);
int
ecall_strlen(struct A *a);
int
ecall_read_buffer(int *out, int size);
int
ecall_count();
void *
ecall_get_addr(void *x);

void
ecall_test_func_0();
void
ecall_test_func_1(int a);
void
ecall_test_func_3(int a, int b, int c);
void
ecall_test_func_5(int a, int b, int c, int d, int e);
void
ecall_test_func_10(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
void
ecall_test_func_15(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o);


#endif
