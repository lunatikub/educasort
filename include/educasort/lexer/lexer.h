/**
 * @file lexer.h
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef EDUCASORT_LEXER_H__
#define EDUCASORT_LEXER_H__

#include <stddef.h>
#include <stdbool.h>

enum token_type {
  TOKEN_NULL,

  TOKEN_IDENTIFIER, /* [_a-zA-Z]* */
  TOKEN_NUMBER, /* [0-9]* */

  /** Punctuation Marks **/
  TOKEN_OPENING_PARENT, /* ( */
  TOKEN_CLOSING_PARENT, /* ) */
  TOKEN_OPENING_BRACE, /* { */
  TOKEN_CLOSING_BRACE, /* } */
  TOKEN_COMA, /* , */
  TOKEN_COLON, /* : */

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

/**
 * Fill the next token.
 *
 * @param sort String to lex.
 * @param len Length of the string.
 * @param tok Token to fill.
 *
 * @return true if the token has been filled, false otherwise.
 */
bool lexer_token_fill(const char *sort, size_t len, struct token *tok);

/**
 * Eat the token filled by @c lexer_token_fill.
 *
 * @param tok Token to eat.
 */
void lexer_token_eat(struct token *tok);

#endif /* !EDUCASORT_LEXER_H__ */
