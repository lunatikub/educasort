/**
 * @file lexer.c
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "internal.h"
#include <educasort/lexer/lexer.h>

static struct token *token_new(struct token_list *tl, size_t offset)
{
  struct token *t = calloc(1, sizeof(*t));
  assert(t != NULL);
  t->start = offset;
  t->tl = tl;
  return t;
}

static bool is_c(char c)
{
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) {
    return true;
  }
  return false;
}

static bool is_d(char d)
{
  if (d >= '0' && d <= '9') {
    return true;
  }
  return false;
}

static void skip(struct token *tok)
{
  const char *algo = tok->tl->algo;
  size_t len = tok->tl->len;

  while (tok->start < len &&
         (algo[tok->start] == ' ' || algo[tok->start] == '\n' || algo[tok->start] == '\t')) {
    if (algo[tok->start] == '\n') {
      ++tok->line;
    }
    ++tok->start;
  }

  tok->end = tok->start;
}

static bool keyword_eq(const char *keyword, const char *str, size_t len)
{
  size_t keyword_len = strlen(keyword);

  if (len != keyword_len) {
    return false;
  }
  if (strncmp(keyword, str, len) == 0) {
    return true;
  }
  return false;
}

static enum token_type keyword_get(const char *str, size_t len)
{
  if (keyword_eq("declaration", str, len)) {
    return TOKEN_DECLARATION;
  }
  if (keyword_eq("integer", str, len)) {
    return TOKEN_TYPE_INTEGER;
  }
  return TOKEN_IDENTIFIER;
}

static void token_string(struct token *tok)
{
  ++tok->end;
  size_t n = tok->end;

  while (n < tok->tl->len && is_c(tok->tl->algo[n])) {
    ++n;
  }
  tok->end = n;

  tok->type = keyword_get(&tok->tl->algo[tok->start], tok->end - tok->start);
}

static void token_number(struct token *tok)
{
  ++tok->end;
  size_t n = tok->end;

  while (n < tok->tl->len && is_d(tok->tl->algo[n])) {
    ++n;
  }

  tok->end = n;
  tok->type = TOKEN_NUMBER;
}

static enum token_type token_basic(char c)
{
  switch (c) {
    case '(': return TOKEN_OPENING_PARENT;
    case ')': return TOKEN_CLOSING_PARENT;
    case '{': return TOKEN_OPENING_BRACE;
    case '}': return TOKEN_CLOSING_BRACE;
    case ',': return TOKEN_COMMA;
    case ':': return TOKEN_COLON;
    case '+': return TOKEN_PLUS;
    case '-': return TOKEN_MINUS;
    case '/': return TOKEN_SLASH;
    case '*': return TOKEN_ASTERISK;
    default: return TOKEN_NULL;
  }
  return TOKEN_NULL;
}

static bool token_fill(struct token *tok)
{
  skip(tok);

  char c = tok->tl->algo[tok->start];

  if ((tok->type = token_basic(c)) != TOKEN_NULL) {
    ++tok->end;
  } else if (is_c(c)) {
    token_string(tok);
  } else if (is_d(c)) {
    token_number(tok);
  } else {
    tok->type = TOKEN_NULL;
    return false;
  }

  return true;
}

static void token_free(struct token_list *tl)
{
  while (!STAILQ_EMPTY(&tl->head)) {
    struct token *iter = STAILQ_FIRST(&tl->head);
    STAILQ_REMOVE_HEAD(&tl->head, next);
    free(iter);
  }
  free(tl);
}

struct token *tokenizer(const char *algo, size_t len)
{
  struct token_list *tl = calloc(1, sizeof(*tl));
  assert(tl != NULL);
  STAILQ_INIT(&tl->head);

  tl->algo = algo;
  tl->len = len;

  size_t offset = 0;
  struct token *tok;

  while (offset != len) {
    tok = token_new(tl, offset);
    STAILQ_INSERT_TAIL(&tl->head, tok, next);
    if (!token_fill(tok)) {
      token_free(tl);
      return NULL;
    }
    ++tl->nr_tok;
    offset = tok->end;
  }

  tok = token_new(tl, offset);
  tok->type = TOKEN_END;
  STAILQ_INSERT_TAIL(&tl->head, tok, next);

  return STAILQ_FIRST(&tl->head);
}

token_t *token_next(token_t *tok)
{
  if (tok == NULL || tok->type == TOKEN_END) {
    return NULL;
  }
  return STAILQ_NEXT(tok, next);
}

enum token_type token_type(struct token *tok)
{
  if (tok == NULL) {
    return TOKEN_NULL;
  }
  return tok->type;
}

void token_destroy(struct token *tok)
{
  if (tok != NULL) {
    token_free(tok->tl);
  }
}
