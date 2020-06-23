/**
 * @file token.c
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 *
 * Utilities to manipulate token.
 */

#include <string.h>

#include <educasort/lexer/lexer.h>
#include <educasort/lexer/token.h>

#include "internal.h"

char* token_strndup(const token_t *tok)
{
  return strndup(&tok->tl->algo[tok->start], tok->end - tok->start);
}

int token_strncmp(const token_t *tok, const char *str, size_t len)
{
  return strncmp(tok->tl->algo + tok->start, str, len);
}
