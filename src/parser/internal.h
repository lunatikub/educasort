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

/**
 * Parse a declaration block.
 */
bool parse_declaration(struct ast_vardec **vardec, struct token **tok, const char *algo, size_t len);

/**
 * Parse a variable list declaration.
 */
bool parse_list_vardec(struct ast_vardec **vardec, struct token **tok, const char *algo, size_t len);

/**
 * Unit-test
 */

PROTOTYPE_FOR_UNIT_TEST(void ast_destroy_vardec(struct ast_vardec *vardec));

#endif /* !PARSER_INTERNAL_H__ */
