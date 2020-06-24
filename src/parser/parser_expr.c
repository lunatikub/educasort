/**
 * @file parser_expr.c
 * @brief Syntax analysis of a sort algorithm
 * @author Thomas Joly
 * @version 0.1
 *
 * Parsing an expression.
 */

#include <stdlib.h>
#include <assert.h>

#include <educasort/lexer/lexer.h>
#include <educasort/lexer/token.h>
#include <educasort/parser/parser.h>

#include "parser_internal.h"

static struct ast_expr *parse_add_sub(struct token **tok);

static struct ast_expr *new_operator(struct ast_expr *lhs, struct ast_expr *rhs,
                                     enum operator_type op)
{
  struct ast_expr *expr = calloc(1, sizeof(*expr));
  assert(expr);

  expr->type = EXPR_OPERATOR;
  expr->op.lhs = lhs;
  expr->op.rhs = rhs;
  expr->op.type = op;

  return expr;
}

static struct ast_expr *new_unary(struct ast_expr *rhs)
{
  struct ast_expr *expr = calloc(1, sizeof(*expr));
  assert(expr);

  expr->type = EXPR_UNARY;
  expr->unary = rhs;

  return expr;
}

static struct ast_expr *new_number(token_t *tok)
{
  struct ast_expr *expr = calloc(1, sizeof(*expr));
  assert(expr);

  expr->type = EXPR_NUMBER;
  expr->number = token_u64(tok);

  return expr;
}

static struct ast_expr *new_var(token_t *tok)
{
  struct ast_expr *expr = calloc(1, sizeof(*expr));
  assert(expr);

  expr->type = EXPR_VAR;
  expr->var = token_strndup(tok);

  return expr;
}

static struct ast_expr *parse_leaf(struct token **tok)
{
  /* Is it a number ? */
  if (token_type(*tok) == TOKEN_NUMBER) {
    struct ast_expr *expr = new_number(*tok);
    *tok = token_next(*tok);
    return expr;
  }

  /* Parenthesis ? */
  if (token_type(*tok) == TOKEN_OPENING_PARENT) {
    *tok = token_next(*tok);
    /* Parse a top-level expression */
    struct ast_expr *expr = parse_add_sub(tok);

    /* Check and skip ')' */
    assert(token_type(*tok) == TOKEN_CLOSING_PARENT);
    *tok = token_next(*tok);
    return expr;
  }

  /* Variable */
  if (token_type(*tok) == TOKEN_IDENTIFIER) {
    struct ast_expr *expr = new_var(*tok);
    *tok = token_next(*tok);
    return expr;
  }

  return NULL;
}

static struct ast_expr *parse_unary(struct token **tok)
{
  while (true) {

    /* Positive operator is a no-op so just skip it */
    if (token_type(*tok) == TOKEN_PLUS) {
      /* Skip */
      *tok = token_next(*tok);
      continue;
    }

    /* Negative operator */
    if (token_type(*tok) == TOKEN_MINUS) {
      /* Skip */
      *tok = token_next(*tok);

      /* Parse rhs
         Note this recurses to self to support negative of a negative */
      struct ast_expr *rhs = parse_unary(tok);

      /* Create unary node */
      return new_unary(rhs);
    }

    /* No positive/negative operator so parse a leaf node */
    return parse_leaf(tok);
  }
}

static struct ast_expr *parse_mult_div(struct token **tok)
{
  /* Parse the left hand side */
  struct ast_expr *lhs = parse_unary(tok);

  while (true) {
    enum operator_type op = OP_NULL;

    // Work out the operator
    if (token_type(*tok) == TOKEN_ASTERISK) {
      op = OP_MULT;
    } else if (token_type(*tok) == TOKEN_SLASH) {
      op = OP_DIV;
    }

    /* Binary operator not found */
    if (op == OP_NULL) {
      return lhs;
    }

    /* Skip the operator */
    *tok = token_next(*tok);

    /* Parse the right hand side of the expression */
    struct ast_expr *rhs = parse_unary(tok);

    /* Create a binary node and use it as the left-hand side from now on */
    lhs = new_operator(lhs, rhs, op);
  }
}

static struct ast_expr *parse_add_sub(struct token **tok)
{
  /* Parse the left hand side */
  struct ast_expr *lhs = parse_mult_div(tok);

  while (true) {
    enum operator_type op = OP_NULL;

    /* Work out the operator */
    if (token_type(*tok) == TOKEN_PLUS) {
      op = OP_ADD;
    } else if (token_type(*tok) == TOKEN_MINUS) {
      op = OP_SUB;
    }

    /* Binary operator not found */
    if (op == OP_NULL) {
      return lhs;
    }

    /* Skip the operator */
    *tok = token_next(*tok);

    /* Parse the right hand side of the expression */
    struct ast_expr *rhs = parse_mult_div(tok);

    /* Create a binary node and use it as the left-hand side from now on */
    lhs = new_operator(lhs, rhs, op);
  }
}

bool parse_expr(struct ast_expr **expr, struct token **tok)
{
  struct ast_expr *new_expr = parse_add_sub(tok);
  *expr = new_expr;
  if (new_expr != NULL) {
    return true;
  }
  return false;
}
