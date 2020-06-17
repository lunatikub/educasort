/**
 * @file parser_declaration.c
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 *
 * Parsing the declaration.
 */

#include <stddef.h>
#include <stdbool.h>

#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>

#include "node.h"
#include "internal.h"

static bool get_var_type(enum token_type tok_type, enum var_type *var_type)
{
  switch (tok_type) {
    case TOKEN_INTEGER:
      *var_type = VAR_INTEGER;
      return true;
    default:
      return false;
  };
  return false;
}

static bool
parse_vardec(struct ast_node **node, struct token *tok,
             const char *sort, size_t len)
{
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  /* Empty declaration. */
  if (tok->type == TOKEN_CLOSING_BRACE) {
    return true;
  }

  struct ast_vardec *vardec_node =
    node_new(NODE_VARDEC, sizeof(*vardec_node));
  node_set(node, vardec_node);

  /* Var name */
  if (tok->type != TOKEN_IDENTIFIER) {
    return false;
  }
  vardec_node->name = token_strndup(sort, tok);
  lexer_token_eat(tok);

  /* Var type */
  if (!lexer_token_fill(sort, len, tok)) {
    return false;
  }
  if (!get_var_type(tok->type, &vardec_node->type)) {
    return false;
  }
  lexer_token_eat(tok);

  lexer_token_fill(sort, len, tok);
  /* New vardec. */
  if (tok->type == TOKEN_COMA) {
    lexer_token_eat(tok);
    return parse_vardec(&vardec_node->node.next, tok, sort, len);
  }
  /* End of declaration. */
  if (tok->type == TOKEN_CLOSING_BRACE) {
    return true;
  }
  return false;
}

bool parse_declaration(struct ast_node *node, struct token *tok,
                       const char *sort, size_t len)
{
  if (!parse_expected(tok, sort, len, TOKEN_DECLARATION)) {
    return false;
  }
  if (!parse_expected(tok, sort, len, TOKEN_OPENING_BRACE)) {
    return false;
  }
  if (!parse_vardec(&node, tok, sort, len)) {
    return false;
  }
  if (!parse_expected(tok, sort, len, TOKEN_CLOSING_BRACE)) {
    return false;
  }
  return true;
}
