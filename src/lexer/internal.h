/**
 * @file internal.h
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef LEXER_INTERNAL_H__
#define LEXER_INTERNAL_H__

#include <educasort/unit-test.h>

enum token_type {
  TOKEN_NULL,

  TOKEN_STRING, /* [_a-zA-Z]* */
  TOKEN_NUMBER, /* [0-9]* */
  TOKEN_OPENING_PARENT, /* ( */
  TOKEN_CLOSING_PARENT, /* ) */
  TOKEN_OPENING_BRACE, /* { */
  TOKEN_CLOSING_BRACE, /* } */
  TOKEN_COMA, /* , */

  /** Keywords (cannot be used as string). **/
  TOKEN_DECLARATION, /* declaration */
  TOKEN_INTEGER, /* integer */

  TOKEN_END,
};

struct token {
  enum token_type type;
  size_t start; /* offset of the token start. */
  size_t end; /* offset of the token end. */
  size_t line;
};

PROTOTYPE_FOR_UNIT_TEST(bool is_c(char c));
PROTOTYPE_FOR_UNIT_TEST(bool is_d(char c));

#endif /* !LEXER_INTERNAL_H__ */
