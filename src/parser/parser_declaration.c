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

#include "parser_internal.h"

bool parse_declaration(struct ast_vardec **vardec, struct token **tok)
{
  /* Empty declaration */
  if (token_type(*tok) == TOKEN_CLOSING_BRACE) {
    return true;
  }
  if (token_type(*tok) != TOKEN_DECLARATION) {
    return false;
  }
  *tok = token_next(*tok);
  if (token_type(*tok) != TOKEN_OPENING_BRACE) {
    return false;
  }
  *tok = token_next(*tok);
  if (!parse_list_vardec(vardec, tok)) {
    return false;
  }
  if (token_type(*tok) != TOKEN_CLOSING_BRACE) {
    return false;
  }
  *tok = token_next(*tok);
  return true;
}
