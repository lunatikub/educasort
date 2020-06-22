/**
 * @file parser_vardec.c
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 *
 * Parsing a variable list declaration.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>

#include "internal.h"

static bool get_var_type(enum token_type tok_type, enum var_type *var_type)
{
  switch (tok_type) {
    case TOKEN_INTEGER: *var_type = VAR_INTEGER; return true;
    default: return false;
  };
  return false;
}

static bool parse_vardec(struct ast_vardec **vardec, struct token *tok, const char *sort,
                         size_t len)
{
  struct ast_vardec *vd = calloc(1, sizeof(*vd));
  assert(vd != NULL);
  *vardec = vd;

  /* Var name */
  if (tok->type != TOKEN_IDENTIFIER) {
    return false;
  }
  vd->var.name = token_strndup(sort, tok);
  lexer_token_eat(tok);

  /* : */
  if (!parse_expected(tok, sort, len, TOKEN_COLON)) {
    return false;
  }

  /* Var type */
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (!get_var_type(tok->type, &vd->var.type)) {
    return false;
  }
  lexer_token_eat(tok);
  return true;
}

static bool is_token_end(enum token_type type)
{
  if (type == TOKEN_CLOSING_BRACE ||
      type == TOKEN_CLOSING_PARENT ||
      type == TOKEN_END) {
    return true;
  }
  return false;
}

bool parse_list_vardec(struct ast_vardec **vardec, struct token *tok, const char *sort, size_t len)
{
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  /* Empty declaration or input. */
  if (is_token_end(tok->type)) {
    return true;
  }
  if (!parse_vardec(vardec, tok, sort, len)) {
    return false;
  }
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (is_token_end(tok->type)) {
    return true;
  }
  /* New vardec. */
  if (tok->type == TOKEN_COMMA) {
    lexer_token_eat(tok);
    return parse_list_vardec(&(*vardec)->next, tok, sort, len);
  }
  return false;
}
