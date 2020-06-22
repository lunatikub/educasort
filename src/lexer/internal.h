/**
 * @file internal.h
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef LEXER_INTERNAL_H__
#define LEXER_INTERNAL_H__

#include <sys/queue.h>
#include <stdbool.h>
#include <stdint.h>

#include <educasort/lexer/lexer.h>

struct token {
  STAILQ_ENTRY(token) next;
  struct token_list *tl; /* backref to token list */
  enum token_type type;
  size_t start; /* offset of the token start. */
  size_t end;   /* offset of the token end. */
  size_t line;
};

struct token_list {
  STAILQ_HEAD(, token) head;
  uint32_t nr_tok;
};

#endif /* !LEXER_INTERNAL_H__ */
