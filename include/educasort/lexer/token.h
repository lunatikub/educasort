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

/**
 * Returns a pointer to a new string which is a duplicate of the string
 * from the token.
 */
char* token_strndup(const char *algo, const token_t *tok);

/**
 * Compare a string with a token.
 */
int token_strncmp(const token_t *tok, const char *algo, const char *str,
                  size_t len);

#endif /* !EDUCASORT_TOKEN_H__ */
