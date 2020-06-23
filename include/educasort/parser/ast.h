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
 * Variable.
 */
struct ast_var {
  enum var_type type;
  char *name;
};

/**
 * List of variable declaration node.
 */
struct ast_vardec {
  struct ast_vardec *next;
  struct ast_var var;
};

/**
 * Enumeration of operator type.
 */
enum operator_type {
  OP_NULL,
  OP_ADD,
  OP_SUB,
  OP_MULT,
  OP_DIV,
};

/**
 * Enumaration of expression type.
 */
enum expr_type {
  EXPR_NULL,
  EXPR_OPERATOR,
  EXPR_UNARY,
};

/**
 * Expression node.
 */
struct ast_expr {
  enum expr_type type;
  struct ast_expr *lhs; /* left hand side of the operator */
  struct ast_expr *rhs; /* right hand side of the operator */
  enum operator_type op; /* only used if @c expr_type is an @c EXPR_OPERATOR */
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
