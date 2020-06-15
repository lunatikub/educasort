/**
 * @file lexer.h
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef LEXER_H__
#define LEXER_H__

#include <stddef.h>
#include <stdbool.h>

/* Opaque token structure. */
typedef struct token token_t;

/**
 * Fill the next token.
 *
 * @param sort String to lex.
 * @param len Length of the string.
 * @param tok Token to fill.
 *
 * @return True if the token has been filled, false otherwise.
 */
bool lexer_token_fill(const char *sort, size_t len, token_t *tok);

/**
 * Eat the token filled by @c lexer_token_fill.
 *
 * @param tok Token to eat.
 */
void lexer_token_eat(token_t *tok);

#endif /* !LEXER_H__ */
