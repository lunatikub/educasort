/**
 * @file internal.h
 * @brief Utilities to parse.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef PARSER_INTERNAL_H__
#define PARSER_INTERNAL_H__

#include <educasort/lexer/lexer.h>
#include <educasort/unit-test.h>

#include "token.h"

static inline bool parse_expected(struct token *tok, const char *sort, size_t len,
                                  enum token_type type)
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

bool parse_declaration(struct ast_node **node, struct token *tok, const char *sort, size_t len);

PROTOTYPE_FOR_UNIT_TEST(void ast_destroy_node(struct ast_node *node));

#endif /* !PARSER_INTERNAL_H__ */
