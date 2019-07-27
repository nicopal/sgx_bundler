#ifndef _H_LIB_HOTCALL_CACHE_TRUSTED_
#define _H_LIB_HOTCALL_CACHE_TRUSTED_

#include <stdint.h>
#include "hotcall.h"
#include "hotcall_cache.h"
#include "hotcall-hmap.h"

void
memoize_value(struct memoize *mem, struct hotcall_function_config *config, void *val, void *writeback_hash);
void
invalidate_cache_line(struct memoize *mem, struct memoize_cache *cache, void *val);

#endif
