#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>
#include <educasort/parser/ast.h>

#include <educasort/utils/dot.h>
#include <educasort/utils/string.h>
#include <educasort/utils/convert.h>

#include "parser_internal.h"

static dot_node_t* dump_dot_expr(struct ast_expr *expr, dot_graph_t *graph);

static const char *get_strop(enum operator_type type)
{
  switch (type) {
    case OP_ADD:
      return "+";
    case OP_SUB:
      return "-";
    case OP_MULT:
      return "*";
    case OP_DIV:
      return "/";
    case OP_NULL:
    default:
      assert(!"OP");
  }
}

static dot_node_t* dump_dot_unary(struct ast_expr *expr, dot_graph_t *graph)
{
  dot_node_t *unary_node = dot_node_add(graph, "-", COLOR_GREEN, SHAPE_ELLIPSE);

  dot_node_t *rnode = dump_dot_expr(expr->unary, graph);

  dot_edge_add(graph, unary_node, rnode, NULL, true);
  return unary_node;
}

static dot_node_t* dump_dot_var(struct ast_expr *expr, dot_graph_t *graph)
{
  return dot_node_add(graph, expr->var, COLOR_BLUE, SHAPE_OCTAGON);
}

static dot_node_t* dump_dot_number(struct ast_expr *expr, dot_graph_t *graph)
{
  char str_number[128];
  u64tostr(expr->number, str_number, 128);

  return dot_node_add(graph, str_number, COLOR_BLACK, SHAPE_CIRCLE);
}

static dot_node_t *dump_dot_operator(struct ast_expr *expr, dot_graph_t *graph)
{
  const char *strop = get_strop(expr->op.type);

  dot_node_t *op_node = dot_node_add(graph, strop, COLOR_RED, SHAPE_BOX);

  dot_node_t *lnode = dump_dot_expr(expr->op.lhs, graph);
  dot_node_t *rnode = dump_dot_expr(expr->op.rhs, graph);

  dot_edge_add(graph, op_node, lnode, NULL, true);
  dot_edge_add(graph, op_node, rnode, NULL, true);

  return op_node;
}

static dot_node_t* dump_dot_expr(struct ast_expr *expr, dot_graph_t *graph)
{
  if (expr == NULL) {
    return NULL;
  }

  switch (expr->type) {
    case EXPR_OPERATOR:
      return dump_dot_operator(expr, graph);
    case EXPR_NUMBER:
      return dump_dot_number(expr, graph);
    case EXPR_VAR:
      return dump_dot_var(expr, graph);
    case EXPR_UNARY:
      return dump_dot_unary(expr, graph);
    case EXPR_NULL:
    default:
      assert(!"EXPR");
  }
  return NULL;
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: ./dump_dot_expr expr\n");
    return -1;
  }

  struct ast_expr *expr;

  const char *algo = argv[1];
  size_t len = strlen(algo);

  token_t *tok = tokenizer(algo, len);

  if (!parse_expr(&expr, &tok)) {
    return -1;
  }

  dot_graph_t *graph = dot_graph_new();

  dump_dot_expr(expr, graph);

  string_t *str = string_create(128);
  dot_dump(graph, str);
  printf("%s\n", string_get(str));
  string_destroy(str);
  dot_graph_destroy(graph);

  return 0;
}
