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

static void visit_vardec(const struct visitor *visitor, const struct ast_vardec *vardec)
{
  if (visitor->vardec) {
    visitor->vardec(visitor, vardec);
  }

  if (vardec->next) {
    visit_vardec(visitor, vardec->next);
  }
}

static void visit_sort(const struct visitor *visitor, const struct ast *root)
{
  if (visitor->sort) {
    visitor->sort(visitor, root);
  }
  if (visitor->declaration_start) {
    visitor->declaration_start(visitor);
  }
  if (root->declaration) {
    visit_vardec(visitor, root->declaration);
  }
  if (visitor->declaration_end) {
    visitor->declaration_end(visitor);
  }
}

void visit(const struct ast *root, const struct visitor *visitor)
{
  if (visitor->start) {
    visitor->start(visitor);
  }

  visit_sort(visitor, root);

  if (visitor->end) {
    visitor->end(visitor);
  }
}
