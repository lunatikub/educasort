/**
 * @file convert.h
 * @brief Convert string and number to/from string and number.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef EDUCASORT_CONVERT_H__
#define EDUCASORT_CONVERT_H__

#include <stdbool.h>

bool strtoi32(const char *start, const char *end, int32_t *v);

bool strtoi64(const char *start, const char *end, int64_t *v);

bool strtou32(const char *start, const char *end, uint32_t *v);

bool strtou64(const char *start, const char *end, uint64_t *v);

bool u64tostr(uint64_t u64, char *v, size_t len);

bool u32tostr(uint32_t u32, char *v, size_t len);

#endif /* !EDUCASORT_CONVERT_H__ */
