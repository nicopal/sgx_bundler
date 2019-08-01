#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */

#include "hotcall_bundler_sample.h"
#include "hotcall_bundler_sample_t.h"  /* print_string */
#include "functions.h"
#include "hotcall_config.h"
#include "ecall_wrappers.h"
#include "ecalls.h"

#include <math.h>

#define CALL_TABLE_CAPACITY 256

void *call_table[CALL_TABLE_CAPACITY] = {
    [hotcall_ecall_always_true] = wrapper_ecall_always_true,
    [hotcall_ecall_always_false] = wrapper_ecall_always_false,
    [hotcall_ecall_foo] = wrapper_ecall_foo,
    [hotcall_ecall_plus_one] = wrapper_ecall_plus_one,
    [hotcall_ecall_greater_than_two] = wrapper_ecall_greater_than_two,
    [hotcall_ecall_plus_one_ret] = wrapper_ecall_plus_one_ret,
    [hotcall_ecall_plus] = wrapper_ecall_plus,
    [hotcall_ecall_plus_y] = wrapper_ecall_plus_y,
    [hotcall_ecall_zero] = wrapper_ecall_zero,
    [hotcall_ecall_plus_y_v2] = wrapper_ecall_plus_y_v2,
    [hotcall_ecall_count] = wrapper_ecall_count,
    [hotcall_ecall_read_buffer] = wrapper_ecall_read_buffer,
    [hotcall_ecall_change_ptr_to_ptr] = wrapper_ecall_change_ptr_to_ptr,
    [hotcall_ecall_container_of] = wrapper_ecall_container_of,
    [hotcall_ecall_offset_of] = wrapper_ecall_offset_of,
    [hotcall_ecall_container_of_ret] = wrapper_ecall_container_of_ret,
    [hotcall_ecall_offset_of_ret] = wrapper_ecall_offset_of_ret,
    [hotcall_ecall_strlen] = wrapper_ecall_strlen,
    [hotcall_ecall_greater_than_y] = wrapper_ecall_greater_than_y,
    [hotcall_ecall_plus_plus] = wrapper_ecall_plus_plus,
    [hotcall_ecall_for_each_10_test] = wrapper_ecall_for_each_10_test,
    [hotcall_ecall_add_and_count] = wrapper_ecall_add_and_count,
    [hotcall_ecall_test_func_0] = wrapper_ecall_test_func_0,
    [hotcall_ecall_test_func_1] = wrapper_ecall_test_func_1,
    [hotcall_ecall_test_func_3] = wrapper_ecall_test_func_3,
    [hotcall_ecall_test_func_5] = wrapper_ecall_test_func_5,
    [hotcall_ecall_test_func_10] = wrapper_ecall_test_func_10,
    [hotcall_ecall_test_func_15] = wrapper_ecall_test_func_15
};

void
ecall_configure_hotcall() {
    struct hotcall_config conf = {
        .call_table = call_table
    };
    struct hotcall_config *config = malloc(sizeof(struct hotcall_config));
    memcpy(config, &conf, sizeof(struct hotcall_config));
    hotcall_register_config(config);
}

void printf(const char *fmt, ...) {
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print(buf);
}
