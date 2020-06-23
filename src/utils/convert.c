/**
 * @file convert.c
 * @brief Convert string and number to/from string and number.
 * @author Thomas Joly
 * @version 0.1
 */

#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include <educasort/utils/convert.h>

bool strtoi32(const char *start, const char *end, int32_t *v)
{
  char *endptr = NULL;
  long val;
  size_t len = end - start;
  errno = 0;

  if (start == NULL || end == NULL || end < start || len == 0) {
    return false;
  }

  val = strtol(start, &endptr, 10);

  if (endptr != end) {
    return false;
  }

  if (errno == ERANGE || val < INT32_MIN || val > INT32_MAX) {
    return false;
  }

  *v = val;
  return true;
}

bool strtoi64(const char *start, const char *end, int64_t *v)
{
  char *endptr = NULL;
  long long int val;
  size_t len = end - start;
  errno = 0;

  if (start == NULL || end == NULL || end < start || len == 0) {
    return false;
  }

  val = strtoll(start, &endptr, 10);

  if (endptr != end) {
    return false;
  }

  if (errno == ERANGE || val < INT64_MIN || val > INT64_MAX) {
    return false;
  }

  *v = val;
  return true;
}

bool strtou32(const char *start, const char *end, uint32_t *v)
{
  char *endptr = NULL;
  unsigned long val;
  size_t len = end - start;
  errno = 0;

  if (start == NULL || end == NULL || end < start || len == 0) {
    return false;
  }

  val = strtoul(start, &endptr, 10);

  if (endptr != end) {
    return false;
  }

  if (errno == ERANGE || val > UINT32_MAX) {
    return false;
  }

  *v = val;
  return true;
}

bool strtou64(const char *start, const char *end, uint64_t *v)
{
  char *endptr = NULL;
  unsigned long long int val;
  size_t len = end - start;
  errno = 0;

  if (start == NULL || end == NULL || end < start || len == 0) {
    return false;
  }

  val = strtoull(start, &endptr, 10);

  if (endptr != end) {
    return false;
  }

  if (errno == ERANGE || val > UINT64_MAX) {
    return false;
  }

  *v = val;
  return true;
}

bool u64tostr(uint64_t u64, char *v, size_t len)
{
  int n = snprintf(v, len, "%lu", u64);

  if (n >= len) {
    return false;
  }

  return true;
}

bool u32tostr(uint32_t u32, char *v, size_t len)
{
  int n = snprintf(v, len, "%u", u32);

  if (n >= len) {
    return false;
  }

  return true;
}
