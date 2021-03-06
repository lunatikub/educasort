/**
 * @file parser.c
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#include <string.h>

#include <educasort/lexer/lexer.h>
#include <educasort/lexer/token.h>
#include <educasort/parser/parser.h>

#include "parser_internal.h"

static bool parse_sort_name(struct ast *root, struct token **tok)
{
  if (token_type(*tok) != TOKEN_IDENTIFIER) {
    return false;
  }
  root->name = token_strndup(*tok);
  *tok = token_next(*tok);
  return true;
}

static bool parse_input(struct ast *root, struct token **tok)
{
  if (token_type(*tok) != TOKEN_OPENING_PARENT) {
    return false;
  }
  *tok = token_next(*tok);

  if (!parse_list_vardec(&root->input, tok)) {
    return false;
  }

  if (token_type(*tok) != TOKEN_CLOSING_PARENT) {
    return false;
  }
  *tok = token_next(*tok);
  return true;
}

static bool parse_sort(struct ast *root, token_t **tok)
{
  if (!parse_sort_name(root, tok)) {
    return false;
  }
  if (!parse_input(root, tok)) {
    return false;
  }
  if (token_type(*tok) != TOKEN_OPENING_BRACE) {
    return false;
  }
  *tok = token_next(*tok);
  if (!parse_declaration(&root->declaration, tok)) {
    return false;
  }
  if (token_type(*tok) != TOKEN_CLOSING_BRACE) {
    return false;
  }
  *tok = token_next(*tok);
  return true;
}

bool parse(struct ast *ast, const char *algo, size_t len)
{
  bool ret;
  token_t *tok = tokenizer(algo, len);

  memset(ast, 0, sizeof(*ast));
  ret = parse_sort(ast, &tok);
  token_destroy(tok);

  return ret;
}
