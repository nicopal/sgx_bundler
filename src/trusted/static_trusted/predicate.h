#ifndef _H_BOOLEAN_EXPRESSION_H
#define _H_BOOLEAN_EXPRESSION_H

#include "hotcall_config.h"
#include "hotcall_function.h"
#include "hotcall_utils.h"
#include <stddef.h>
#include "parameter.h"
#include "execute_function.h"
#include "hotcall_if.h"

#define OFFSET(ARG, TYPE, OFFSET) ((TYPE) ARG + OFFSET)
#define OFFSET_DEREF(ARG, TYPE, OFFSET) *((TYPE) ARG + OFFSET)

enum input_type { OPERATOR, VARIABLE, VECTOR, POINTER, OPERAND, FUNCTION, NEGATION };
struct input_item {
    int ch;
    enum input_type type;
};

int
evaluate_predicate(struct postfix_item *predicate_postfix, unsigned int postfiX_length, const struct hotcall_config *hotcall_config, int offset);
void
evaluate_predicate_batch(struct postfix_item *predicate_postfix, unsigned int postfix_length, const struct hotcall_config *hotcall_config, int n, int result[n], int offset);

#endif
