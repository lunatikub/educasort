/**
 * @file ast.c
 * @brief Abstract syntax tree of the sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#include <stdlib.h>

#include <educasort/parser/ast.h>

#include "internal.h"

static void ast_destroy_vardec_node(struct ast_node *node)
{
  struct ast_vardec *vardec_node = ast_vardec_get(node);
  free(vardec_node->name);
  free(node);
}

static void ast_destroy_sort_node(struct ast_node *node)
{
  struct ast_sort *sort_node = ast_sort_get(node);
  free(sort_node->name);
  free(node);
}

PRIVATE_EXCEPT_UNIT_TEST
void ast_destroy_node(struct ast_node *node)
{
  if (node == NULL) {
    return;
  }

  ast_destroy_node(node->next);
  ast_destroy_node(node->child);

  switch (node->type) {
    case NODE_SORT:
      ast_destroy_sort_node(node);
      break;
    case NODE_VARDEC:
      ast_destroy_vardec_node(node);
      break;
    default:
      break;
  };
}

void ast_destroy(struct ast *ast)
{
  ast_destroy_node(&ast->root);
}
