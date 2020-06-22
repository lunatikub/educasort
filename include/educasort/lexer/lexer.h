/**
 * @file lexer.h
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef EDUCASORT_LEXER_H__
#define EDUCASORT_LEXER_H__

#include <stdbool.h>
#include <stddef.h>

enum token_type {
  TOKEN_NULL,

  TOKEN_IDENTIFIER, /* [_a-zA-Z]* */
  TOKEN_NUMBER,     /* [0-9]* */

  /* Basics */
  TOKEN_OPENING_PARENT, /* ( */
  TOKEN_CLOSING_PARENT, /* ) */
  TOKEN_OPENING_BRACE,  /* { */
  TOKEN_CLOSING_BRACE,  /* } */
  TOKEN_COMMA,          /* , */
  TOKEN_COLON,          /* : */
  TOKEN_PLUS, /* + */
  TOKEN_MINUS, /* - */
  TOKEN_ASTERISK, /* * */
  TOKEN_SLASH, /* / */

  /** Keywords **/
  TOKEN_DECLARATION, /* declaration */
  TOKEN_TYPE_INTEGER,

  TOKEN_END,
};

/** Opaque structure to manipulate token. **/
typedef struct token token_t;

/**
 * Get the list of tokens from a stirng input.
 *
 * @param sort String input.
 * @param len Length of the string.
 * @return The first token if succeeded, otherwise return @c NULL.
 */
token_t* tokenizer(const char *sort, size_t len);

/**
 * Get the next token.
 *
 * @param tok Current token.
 * @return Next token if succeeded, otherwise return @c NULL.
 */
token_t* token_next(token_t *tok);

/**
 * Get the type of a token.
 *
 * @param tok Current token.
 * @return Token type if succeeded, otherwise return @C TOKEN_NULL.
 */
enum token_type token_type(token_t *tok);

/**
 * Destroy the list of tokens previously created by @c tokenizer.
 *
 * @param tok Any token from @c tokenizer.
 */
void token_destroy(token_t *tok);

#endif /* !EDUCASORT_LEXER_H__ */
