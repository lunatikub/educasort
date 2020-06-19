/**
 * @file parser_declaration.c
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 *
 * Parsing a declaration.
 */

#include <stdbool.h>
#include <stddef.h>

#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>

#include "internal.h"

bool parse_declaration(struct ast_vardec **vardec, struct token *tok, const char *sort, size_t len)
{
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  /* Empty declaration */
  if (tok->type == TOKEN_CLOSING_BRACE) {
    return true;
  }
  if (tok->type != TOKEN_DECLARATION) {
    return false;
  }
  lexer_token_eat(tok);

  if (!parse_expected(tok, sort, len, TOKEN_OPENING_BRACE)) {
    return false;
  }
  if (!parse_list_vardec(vardec, tok, sort, len)) {
    return false;
  }
  if (!parse_expected(tok, sort, len, TOKEN_CLOSING_BRACE)) {
    return false;
  }
  return true;
}
