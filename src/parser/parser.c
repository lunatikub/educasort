/**
 * @file parser.c
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>

static void node_set(struct ast_node **dst, void *src)
{
  *dst = (struct ast_node*)src;
}

static void node_init(struct ast_node *node, enum node_type type)
{
  node->next = NULL;
  node->child = NULL;
  node->type = type;
}

static void* node_new(enum node_type type, size_t sz)
{
  struct ast_node *node = malloc(sz);
  assert(node != NULL);
  node_init(node, type);
  return node;
}

static char* token_strndup(const char *sort, const struct token *tok)
{
  return strndup(&sort[tok->start], tok->end - tok->start);
}

static int token_strncmp(const struct token *tok, const char *sort, const char *str, size_t len)
{
  return strncmp(sort + tok->start, str, len);
}

static bool
parse_name(struct ast_sort *node, struct token *tok,
           const char *sort, size_t len)
{
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (tok->type != TOKEN_STRING) {
    return false;
  }
  node->name = token_strndup(sort, tok);
  lexer_token_eat(tok);
  return true;
}

static bool
parse_expected(struct token *tok, const char *sort, size_t len, enum token_type type)
{
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (tok->type != type) {
    return false;
  }
  lexer_token_eat(tok);
  return true;
}

/**
 * (A)
 */
static bool
parse_A(struct token *tok, const char *sort, size_t len)
{
  /* ( */
  if (!parse_expected(tok, sort, len, TOKEN_OPENING_PARENT)) {
    return false;
  }

  /* A */
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (tok->type != TOKEN_STRING) {
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
static bool
parse_sort(struct ast_node *root, struct token *tok,
           const char *sort, size_t len)
{
  struct ast_sort *node = node_new(NODE_SORT, sizeof(*node));

  if (!parse_name(node, tok, sort, len)) {
    return false;
  }
  if (!parse_A(tok, sort, len)) {
    return false;
  }

  node_set(&root->child, node);
  return true;
}

bool parse(struct ast *ast, const char *sort, size_t len)
{
  struct token tok = {
    .start = 0,
    .line = 1,
    .type = TOKEN_NULL,
  };

  node_init(&ast->root, NODE_ROOT);

  if (!parse_sort(&ast->root, &tok, sort, len)) {
    return false;
  }
  return true;
}
