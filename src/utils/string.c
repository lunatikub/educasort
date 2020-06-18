/**
 * @file string.c
 * @brief Manipulate string.
 * @author Thomas Joly
 * @version 0.1
 */

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <educasort/utils/string.h>

#include "internal.h"

struct string {
  char *data;
  size_t len;
  size_t capa;
};

PRIVATE_EXCEPT_UNIT_TEST
size_t string_capa(const struct string *str)
{
  return str->capa;
}

PRIVATE_EXCEPT_UNIT_TEST
size_t string_len(const struct string *str)
{
  return str->len;
}

const char *string_get(const struct string *str)
{
  return str->data;
}

struct string *string_create(size_t initial_capa)
{
  struct string *s = malloc(sizeof(*s));
  assert(s != NULL);

  s->data = malloc(initial_capa + 1);
  s->capa = initial_capa;
  s->len = 0;

  return s;
}

void string_destroy(struct string *str)
{
  free(str->data);
  free(str);
}

static void string_inc_capa(struct string *str, size_t len)
{
  while (str->capa - str->len < len) {
    str->capa *= 2;
    char *tmp = malloc(str->capa + 1);
    assert(tmp != NULL);
    memcpy(tmp, str->data, str->len);
    free(str->data);
    str->data = tmp;
  }
}

void string_append(struct string *dst, const char *src)
{
  size_t len = strlen(src);
  string_inc_capa(dst, len);
  memcpy(dst->data + dst->len, src, len);
  dst->len += len;
  dst->data[dst->len] = '\0';
}
