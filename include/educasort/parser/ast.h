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
 * Enumeration of variable type.
 */
enum var_type {
  VAR_INTEGER,
};

/**
 * Variable declaration node.
 */
struct ast_vardec {
  struct ast_vardec *next;
  char *name;
  enum var_type type;
};

/**
 * Abstract syntax tree root node.
 */
struct ast {
  char *name;
  struct ast_vardec *input;
  struct ast_vardec *declaration;
};

/**
 * Destroy (free) an abstract syntax tree.
 *
 * @param ast Abstract syntax tree to destroy.
 */
void ast_destroy(struct ast *ast);

#endif /* !EDUCASORT_AST_H__ */
