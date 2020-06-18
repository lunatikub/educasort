/**
 * @file visitor.c
 * @brief Visitor of the sort AST.
 * @author Thomas Joly
 * @version 0.1
 *
 * AST visitor separates algorithm from the object
 * structure on which it operates.
 */

#include <educasort/visitor/visitor.h>

static void visit_vardec(const struct visitor *visitor, const struct ast_node *node)
{
  const struct ast_vardec *vardec_node = ast_vardec_get(node);

  if (visitor->vardec) {
    visitor->vardec(visitor, vardec_node);
  }

  if (vardec_node->node.next) {
    visit_vardec(visitor, vardec_node->node.next);
  }
}

static void visit_sort(const struct visitor *visitor, const struct ast_node *node)
{
  const struct ast_sort *sort_node = ast_sort_get(node);

  if (visitor->sort) {
    visitor->sort(visitor, sort_node);
  }
  if (visitor->declaration_start) {
    visitor->declaration_start(visitor);
  }
  if (sort_node->node.next) {
    visit_vardec(visitor, sort_node->node.next);
  }
  if (visitor->declaration_end) {
    visitor->declaration_end(visitor);
  }
}

void visit(const struct ast *ast, const struct visitor *visitor)
{
  const struct ast_node *root = &ast->root;

  if (visitor->start) {
    visitor->start(visitor);
  }

  visit_sort(visitor, root->child);

  if (visitor->end) {
    visitor->end(visitor);
  }
}
