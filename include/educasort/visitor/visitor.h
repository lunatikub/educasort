/**
 * @file visitor.h
 * @brief Visitor of the sort AST.
 * @author Thomas Joly
 * @version 0.1
 *
 * AST visitor separates algorithm from the object
 * structure on which it operates.
 */

#ifndef VISITOR_H__
#define VISITOR_H__

#include <stdbool.h>

#include <educasort/parser/ast.h>

struct visitor {
  /**
   * Start/End.
   */
  void (*start)(const struct visitor *visitor);
  void (*end)(const struct visitor *visitor);
  /**
   * Sort.
   */
  void (*sort)(const struct visitor *visitor, const struct ast *root);
  /**
   * Declaration.
   */
  void (*declaration_start)(const struct visitor *visitor);
  void (*vardec)(const struct visitor *visitor, const struct ast_vardec *vardec);
  void (*declaration_end)(const struct visitor *visitor);
};

/**
 * Visit the AST with a specific visitor.
 *
 * @param ast Abstract syntax tree to visit.
 * @param visitor Specific visitor.
 */
void visit(const struct ast *ast, const struct visitor *visitor);

#endif /* !VISITOR_H_ */
