/**
 * @file token.h
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 *
 * Utilities to manipulate token.
 */

#ifndef EDUCASORT_TOKEN_H__
#define EDUCASORT_TOKEN_H__

#include <stdint.h>

/**
 * Returns a pointer to a new string which is a duplicate of the string
 * from the token.
 */
char *token_strndup(const token_t *tok);

/**
 * Compare a string with a token.
 */
int token_strncmp(const token_t *tok, const char *str, size_t len);

/**
 * Returns a uint64_t from a a token.
 */
uint64_t token_u64(const token_t *tok);

#endif /* !EDUCASORT_TOKEN_H__ */
