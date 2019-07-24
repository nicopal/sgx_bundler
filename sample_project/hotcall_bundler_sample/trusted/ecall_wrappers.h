#ifndef _H_ECALL_WRAPPERS_
#define _H_ECALL_WRAPPERS_

#include "functions.h"
#include "ecalls.h"

static void
wrapper_ecall_add_and_count(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(int *) args[n_params - 1][i] = ecall_add_and_count(*(int *) args[0][i], *(int *) args[1][i], (int *) args[2][i]);
    }
}

static void
wrapper_ecall_get_addr(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        args[n_params - 1][i] = ecall_get_addr(args[0][i]);
    }
}

static void
wrapper_ecall_greater_than_y(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(bool *) args[n_params - 1][i] = ecall_greater_than_y((int *) args[0][i], *(int *) args[1][i]);
    }
}

static void
wrapper_ecall_plus_one(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_plus_one((int *) args[0][i]);
    }
}

static void
wrapper_ecall_always_true(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(bool *) args[n_params - 1][i] = ecall_always_true();
    }
}

static void
wrapper_ecall_always_false(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(bool *) args[n_params - 1][i] = ecall_always_false();
    }
}

static void
wrapper_ecall_foo(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_foo();
    }
}

static void
wrapper_ecall_bar(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_bar();
    }
}

static void
wrapper_ecall_greater_than_two(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(bool *) args[n_params - 1][i] = ecall_greater_than_two((int *) args[0][i]);
    }
}

static void
wrapper_ecall_plus_plus(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_plus_plus((int *) args[0][i], (int *) args[1][i]);
    }
}

static void
wrapper_ecall_plus_one_ret(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(int *) args[n_params - 1][i] = ecall_plus_one_ret(*(int *) args[0][i]);
    }
}

static void
wrapper_ecall_plus_one_ret_v2(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(int *) args[n_params - 1][i] = ecall_plus_one_ret_v2(*(int *) args[0][i], *(int *) args[1][i], *(int *) args[2][i], *(int *) args[3][i], *(int *) args[4][i]);
    }
}

static void
wrapper_ecall_plus(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(int *) args[n_params - 1][i] = ecall_plus(*(int *) args[0][i], *(int *) args[1][i]);
    }
}

static void
wrapper_ecall_revert(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(bool *) args[n_params - 1][i] = ecall_revert(*(bool *) args[0][i]);
    }
}


static void
wrapper_ecall_plus_y(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_plus_y((int *) args[0][i], *(int *) args[1][i]);
    }
}

static void
wrapper_ecall_plus_y_v2(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_plus_y_v2(*(int *) args[0][i], (int *) args[1][i]);
    }
}

static void
wrapper_ecall_zero(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_zero((int *) args[0][i]);
    }
}

static void
wrapper_ecall_read_buffer(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(int *) args[n_params - 1][i] = ecall_read_buffer((int *) args[0][i], *(int *) args[1][i]);
    }
}

static void
wrapper_ecall_count(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(int *) args[n_params - 1][i] = ecall_count();
    }
}

static void
wrapper_ecall_change_ptr_to_ptr(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_change_ptr_to_ptr((int **) args[0][i], (int *) args[1][i]);
    }
}

static void
wrapper_ecall_container_of(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_offset_of(args[0][i], -(*(int *) args[1][i]));
    }
}

static void
wrapper_ecall_offset_of(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_offset_of(args[0][i], *(int *) args[1][i]);
    }
}

static void
wrapper_ecall_offset_of_ret(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(void **) args[n_params - 1][i] = ecall_offset_of_ret(args[0], *(unsigned int *) args[1][i]);
    }
}

static void
wrapper_ecall_container_of_ret(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(void **) args[n_params - 1][i] = ecall_offset_of_ret(args[0], -(*(unsigned int *) args[1][i]));
    }
}

static void
wrapper_ecall_strlen(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        *(int *) args[n_params - 1][i] = ecall_strlen(args[0][i]);
    }
}

static void
wrapper_ecall_for_each_10_test(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_for_each_10_test(*(uint8_t *) args[0][i], *(uint8_t *) args[1][i], (int *) args[2][i], *(unsigned int *) args[3][i], *(unsigned int *) args[4][i]);
    }
}

static void
wrapper_ecall_test_func_0(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_test_func_0();
    }
}

static void
wrapper_ecall_test_func_1(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_test_func_1(*(int *) args[0][i]);
    }
}

static void
wrapper_ecall_test_func_3(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_test_func_3(*(int *) args[0][i], *(int *) args[1][i], *(int *) args[2][i]);
    }
}

static void
wrapper_ecall_test_func_5(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
        ecall_test_func_5(
            *(int *) args[0][i],
            *(int *) args[1][i],
            *(int *) args[2][i],
            *(int *) args[3][i],
            *(int *) args[4][i]
        );
    }
}

static void
wrapper_ecall_test_func_10(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
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
    }
}

static void
wrapper_ecall_test_func_15(unsigned int n_iters, unsigned int n_params, void *args[n_params][n_iters]) {
    for(int i = 0; i < n_iters; ++i) {
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
    }
}

#endif
