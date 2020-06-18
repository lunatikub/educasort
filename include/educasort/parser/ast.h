/**
 * @file ast.h
 * @brief Abstract syntax tree of the sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef EDUCASORT_AST_H__
#define EDUCASORT_AST_H__

#include <stdint.h>

#include <educasort/utils/utils.h>

/**
 * Enumeration of node type.
 */
enum node_type {
  NODE_ROOT,
  NODE_SORT,
  NODE_VARDEC,
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
 * Enumeration of variable type.
 */
enum var_type {
  VAR_INTEGER,
};

#define ast_vardec_get(n) (container_of(n, struct ast_vardec, node))

/**
 * Variable declaration node.
 * type: NODE_VARDEC
 * next: ast_vardec
 * child: NULL
 */
struct ast_vardec {
  struct ast_node node;
  char *name;
  enum var_type type;
};

#define ast_sort_get(n) (container_of(n, struct ast_sort, node))

/**
 * Sort node.
 * type: NODE_SORT
 * next: ast_vardec
 * child: NULL
 */
struct ast_sort {
  struct ast_node node;
  char *name;
};

/**
 * Root node.
 * type: NODE_ROOT
 * next: NULL
 * child: ast_sort
 */
struct ast {
  struct ast_node root;
};

/**
 * Destroy (free) an abstract syntax tree.
 *
 * @param ast Abstract syntax tree to destroy.
 */
void ast_destroy(struct ast *ast);

#endif /* !EDUCASORT_AST_H__ */
