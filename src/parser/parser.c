/**
 * @file parser.c
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>

#include "internal.h"
#include "node.h"

/**
 * SortName
 */
static bool parse_sort_name(struct ast_sort *node, struct token *tok, const char *sort, size_t len)
{
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (tok->type != TOKEN_IDENTIFIER) {
    return false;
  }
  node->name = token_strndup(sort, tok);
  lexer_token_eat(tok);
  return true;
}

/**
 * (A)
 */
static bool parse_A(struct token *tok, const char *sort, size_t len)
{
  /* ( */
  if (!parse_expected(tok, sort, len, TOKEN_OPENING_PARENT)) {
    return false;
  }

  /* A */
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (tok->type != TOKEN_IDENTIFIER) {
    return false;
  }
  if (token_strncmp(tok, sort, "A", 1) != 0) {
    return false;
  }
  lexer_token_eat(tok);

  /* ) */
  if (!parse_expected(tok, sort, len, TOKEN_CLOSING_PARENT)) {
    return false;
  }
  return true;
}

/**
 * SortName(A) {
 *   declaration { ... }
 * }
 */
static bool parse_sort(struct ast_node *root, struct token *tok, const char *sort, size_t len)
{
  struct ast_sort *node = node_new(NODE_SORT, sizeof(*node));
  node_set(&root->child, node);

  if (!parse_sort_name(node, tok, sort, len)) {
    return false;
  }
  if (!parse_A(tok, sort, len)) {
    return false;
  }
  if (!parse_expected(tok, sort, len, TOKEN_OPENING_BRACE)) {
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
  node_init(&ast->root, NODE_ROOT);

  if (!parse_sort(&ast->root, &tok, sort, len)) {
    return false;
  }
  return true;
}
