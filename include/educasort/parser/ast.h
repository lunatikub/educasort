/**
 * @file lexer.h
 * @brief Lexical analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef AST_H__
#define AST_H__

#include <stdint.h>

#include <educasort/utils.h>

enum node_type {
  NODE_ROOT,
  NODE_SORT,
};

/**
 * Generic node.
 */
struct ast_node {
  enum node_type type;
  struct ast_node *next;
  struct ast_node *child;
};

/**
 * Sort node
 * next -> NULL
 * child -> declaration
 */
struct ast_sort {
  struct ast_node node;
  const char *name;
};

/**
 * Root node
 * next -> NULL
 * child -> sort node
 */
struct ast {
  struct ast_node root;
};

#endif /* !AST_H__ */
