/**
 * @file token.h
 * @brief Utilities to manipulate token.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef TOKEN_H__
#define TOKEN_H__

#include <string.h>

static inline char *token_strndup(const char *sort, const struct token *tok)
{
  return strndup(&sort[ tok->start ], tok->end - tok->start);
}

static inline int token_strncmp(const struct token *tok, const char *sort, const char *str,
                                size_t len)
{
  return strncmp(sort + tok->start, str, len);
}

static inline void token_init(struct token *tok)
{
  tok->start = 0;
  tok->line = 1;
  tok->type = TOKEN_NULL;
}

#endif /* !TOKEN_H__ */
