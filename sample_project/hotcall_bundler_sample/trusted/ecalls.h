#ifndef _H_ECALLS_
#define _H_ECALLS_

#include <stdbool.h>
#include <stdint.h>

struct A { int x; int y; };

#define HOTCALL_WRAPPER(ECALL, BODY...) \
  static inline void wrapper_ ## ECALL(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {\
      for(int i = 0; i < n_iters; ++i) { \
          BODY \
      }\
  }

bool
ecall_always_true();
bool
ecall_always_false();
void
ecall_foo();
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

void
ecall_for_each_10_test(uint8_t bridge_id, uint8_t table_id, int *buf, unsigned grp_prio, unsigned int user_prio);

HOTCALL_WRAPPER(ecall_always_true, { *(bool *) args[n_params - 1][i] = ecall_always_true(); });
HOTCALL_WRAPPER(ecall_always_false, { *(bool *) args[n_params - 1][i] = ecall_always_false(); });
HOTCALL_WRAPPER(ecall_foo, { ecall_foo(); });
HOTCALL_WRAPPER(ecall_plus_one, { ecall_plus_one(args[0][i]); });
HOTCALL_WRAPPER(ecall_plus_one_ret, { *(int *) args[n_params - 1][i] = ecall_plus_one_ret(*(int *) args[0][i]); });
HOTCALL_WRAPPER(ecall_greater_than_two, { *(bool *) args[n_params - 1][i] = ecall_greater_than_two(args[0][i]); });
HOTCALL_WRAPPER(ecall_greater_than_y, { *(bool *) args[n_params - 1][i] = ecall_greater_than_y(args[0][i], *(int *) args[1][i]); });
HOTCALL_WRAPPER(ecall_plus_plus, { ecall_plus_plus(args[0][i], args[1][i]); });
HOTCALL_WRAPPER(ecall_plus, { *(int *) args[n_params - 1][i] = ecall_plus(*(int *) args[0][i], *(int *) args[1][i]); });
HOTCALL_WRAPPER(ecall_plus_y, { ecall_plus_y(args[0][i], *(int *) args[1][i]); });
HOTCALL_WRAPPER(ecall_plus_y_v2, { ecall_plus_y_v2(*(int *) args[0][i], args[1][i]); });
HOTCALL_WRAPPER(ecall_zero, { ecall_zero(args[0][i]); });
HOTCALL_WRAPPER(ecall_count, { *(int *) args[n_params - 1][i] = ecall_count(); });
HOTCALL_WRAPPER(ecall_read_buffer, { *(int *) args[n_params - 1][i] = ecall_read_buffer(args[0][i], *(int *) args[1][i]); });
HOTCALL_WRAPPER(ecall_change_ptr_to_ptr, { ecall_change_ptr_to_ptr(args[0][i], args[1][i]); });
HOTCALL_WRAPPER(ecall_offset_of, { ecall_offset_of(args[0][i], *(int *) args[1][i]); });
HOTCALL_WRAPPER(ecall_offset_of_ret, { *(void **) args[n_params - 1][i] = ecall_offset_of_ret(args[0][i], *(unsigned int *) args[1][i]); });
HOTCALL_WRAPPER(ecall_container_of, { ecall_offset_of(args[0][i], -(*(int *) args[1][i])); });
HOTCALL_WRAPPER(ecall_container_of_ret, { *(void **) args[n_params - 1][i] = ecall_offset_of_ret(args[0], *(unsigned int *) args[1][i]); });
HOTCALL_WRAPPER(ecall_strlen, { *(int *) args[n_params - 1][i] = ecall_strlen(args[0][i]); });
HOTCALL_WRAPPER(ecall_for_each_10_test, {
    ecall_for_each_10_test(*(uint8_t *) args[0][i], *(uint8_t *) args[1][i], (int *) args[2][i], *(unsigned int *) args[3][i], *(unsigned int *) args[4][i]);
});
HOTCALL_WRAPPER(ecall_add_and_count, {
    *(int *) args[n_params - 1][i] = ecall_add_and_count(*(int *) args[0][i], *(int *) args[1][i], (int *) args[2][i]);
});
HOTCALL_WRAPPER(ecall_get_addr, {
  args[n_params - 1][i] = ecall_get_addr(args[0][i]);
});
HOTCALL_WRAPPER(ecall_test_func_0, { ecall_test_func_0(); });
HOTCALL_WRAPPER(ecall_test_func_1, {
  ecall_test_func_1(*(int *) args[0][i]);
});
HOTCALL_WRAPPER(ecall_test_func_3, {
  ecall_test_func_3(*(int *) args[0][i], *(int *) args[1][i], *(int *) args[2][i]);

});
HOTCALL_WRAPPER(ecall_test_func_5, {
  ecall_test_func_5(
      *(int *) args[0][i],
      *(int *) args[1][i],
      *(int *) args[2][i],
      *(int *) args[3][i],
      *(int *) args[4][i]
  );
});
HOTCALL_WRAPPER(ecall_test_func_10, {
  ecall_test_func_10(
      *(int *) args[0][i],
      *(int *) args[1][i],
      *(int *) args[2][i],
      *(int *) args[3][i],
      *(int *) args[4][i],
      *(int *) args[5][i],
      *(int *) args[6][i],
      *(int *) args[7][i],
      *(int *) args[8][i],
      *(int *) args[9][i]
  );
});
HOTCALL_WRAPPER(ecall_test_func_15, {
  ecall_test_func_15(
      *(int *) args[0][i],
      *(int *) args[1][i],
      *(int *) args[2][i],
      *(int *) args[3][i],
      *(int *) args[4][i],
      *(int *) args[5][i],
      *(int *) args[6][i],
      *(int *) args[7][i],
      *(int *) args[8][i],
      *(int *) args[9][i],
      *(int *) args[10][i],
      *(int *) args[11][i],
      *(int *) args[12][i],
      *(int *) args[13][i],
      *(int *) args[14][i]
  );
});

#endif
