/**
 * @file lexer.c
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <educasort/lexer/lexer.h>
#include "internal.h"

/* Is it a valid character ? */
PRIVATE_EXCEPT_UNIT_TEST
bool is_c(char c)
{
  if ((c >= 'a' && c <= 'z') ||
      (c >= 'A' && c <= 'Z') ||
      (c == '_')) {
    return true;
  }
  return false;
}

/* Is it a valid digit ? */
PRIVATE_EXCEPT_UNIT_TEST
bool is_d(char d)
{
  if (d >= '0' && d <= '9') {
    return true;
  }
  return false;
}

static void lexer_skip(const char *sort, size_t len, struct token *tok)
{
  while (tok->start < len &&
         (sort[tok->start] == ' ' ||
          sort[tok->start] == '\n' ||
          sort[tok->start] == '\t')) {
    if (sort[tok->start] == '\n') {
      ++tok->line;
    }
    ++tok->start;
  }

  tok->end = tok->start;
}

static void lexer_token_set(struct token *tok, enum token_type type)
{
  tok->type = type;
  ++tok->end;
}

static enum token_type keyword_get(const char *str, size_t len)
{
#define KEYWORD(STR, TOKEN)                     \
  if (sizeof(STR) - 1 == len &&                 \
      strncmp(STR, str, len) == 0)              \
    return TOKEN;

  KEYWORD("declaration", TOKEN_DECLARATION);
  KEYWORD("integer", TOKEN_INTEGER);

#undef KEYWORD

  return TOKEN_IDENTIFIER;
}

static void lexer_string(const char *sort, size_t len, struct token *tok)
{
  ++tok->end;
  size_t n = tok->end;

  while (n < len && is_c(sort[n])) {
    ++n;
  }
  tok->end = n;

  tok->type = keyword_get(&sort[tok->start], tok->end - tok->start);
}

static void lexer_number(const char *sort, size_t len, struct token *tok)
{
  ++tok->end;
  size_t n = tok->end;

  while (n < len && is_d(sort[n])) {
    ++n;
  }

  tok->end = n;
  tok->type = TOKEN_NUMBER;
}

bool lexer_token_fill(const char *sort, size_t len, struct token *tok)
{
  lexer_skip(sort, len, tok);

  if (tok->end == len) {
    tok->type = TOKEN_END;
    return true;
  }

  char c = sort[tok->start];

#define CASE(C, TYPE) case C: lexer_token_set(tok, TYPE); return true
  switch (c) {
    CASE('(', TOKEN_OPENING_PARENT);
    CASE(')', TOKEN_CLOSING_PARENT);
    CASE('{', TOKEN_OPENING_BRACE);
    CASE('}', TOKEN_CLOSING_BRACE);
    CASE(',', TOKEN_COMA);
  };
#undef CASE

#define CASE(COND, NAME) if (COND) { lexer_ ## NAME(sort, len, tok); return true; }
  CASE(is_c(c), string);
  CASE(is_d(c), number);
#undef CASE

  tok->type = TOKEN_NULL;
  return false;
}

void lexer_token_eat(struct token *tok)
{
  tok->start = tok->end;
}
