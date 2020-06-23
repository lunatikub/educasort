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
#include <educasort/lexer/token.h>
#include <educasort/parser/parser.h>

#include "internal.h"

static bool get_var_type(enum token_type tok_type, enum var_type *var_type)
{
  switch (tok_type) {
    case TOKEN_TYPE_INTEGER:
      *var_type = VAR_INTEGER;
      return true;
    default:
      return false;
  };
  return false;
}

static bool parse_vardec(struct ast_vardec **vardec, struct token **tok)
{
  struct ast_vardec *vd = calloc(1, sizeof(*vd));
  assert(vd != NULL);
  *vardec = vd;

  /* Var name */
  if (token_type(*tok) != TOKEN_IDENTIFIER) {
    return false;
  }
  vd->var.name = token_strndup(*tok);
  *tok = token_next(*tok);

  /* : */
  if (token_type(*tok) != TOKEN_COLON) {
    return false;
  }
  *tok = token_next(*tok);

  /* Var type */
  if (!get_var_type(token_type(*tok), &vd->var.type)) {
    return false;
  }
  *tok = token_next(*tok);
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

bool parse_list_vardec(struct ast_vardec **vardec, token_t **tok)
{
  /* Empty declaration or input. */
  if (is_token_end(token_type(*tok))) {
    return true;
  }
  if (!parse_vardec(vardec, tok)) {
    return false;
  }
  if (is_token_end(token_type(*tok))) {
    return true;
  }
  /* New vardec. */
  if (token_type(*tok) == TOKEN_COMMA) {
    *tok = token_next(*tok);
    return parse_list_vardec(&(*vardec)->next, tok);
  }
  return false;
}
