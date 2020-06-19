/**
 * @file parser.c
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>

#include "internal.h"

static bool parse_sort_name(struct ast *root, struct token *tok, const char *sort, size_t len)
{
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (tok->type != TOKEN_IDENTIFIER) {
    return false;
  }
  root->name = token_strndup(sort, tok);
  lexer_token_eat(tok);
  return true;
}

static bool parse_input(struct ast *root, struct token *tok, const char *sort, size_t len)
{
  /* ( */
  if (!parse_expected(tok, sort, len, TOKEN_OPENING_PARENT)) {
    return false;
  }
  if (!parse_list_vardec(&root->input, tok, sort, len)) {
    return false;
  }
  /* ) */
  if (!parse_expected(tok, sort, len, TOKEN_CLOSING_PARENT)) {
    return false;
  }
  return true;
}

static bool parse_sort(struct ast *root, struct token *tok, const char *sort, size_t len)
{
  if (!parse_sort_name(root, tok, sort, len)) {
    return false;
  }
  if (!parse_input(root, tok, sort, len)) {
    return false;
  }
  if (!parse_expected(tok, sort, len, TOKEN_OPENING_BRACE)) {
    return false;
  }
  if (!parse_declaration(&root->declaration, tok, sort, len)) {
    return false;
  }
  if (!parse_expected(tok, sort, len, TOKEN_CLOSING_BRACE)) {
    return false;
  }

  return true;
}

bool parse(struct ast *ast, const char *sort, size_t len)
{
  struct token tok;

  token_init(&tok);
  memset(ast, 0, sizeof(*ast));

  if (!parse_sort(ast, &tok, sort, len)) {
    return false;
  }
  return true;
}
