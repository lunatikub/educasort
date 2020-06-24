/**
 * @file ast.c
 * @brief Abstract syntax tree of the sort algorithm
 * @author Thomas Joly
 * @version 0.1
 */

#include <stdlib.h>

#include <educasort/parser/ast.h>

#include "parser_internal.h"

PRIVATE_EXCEPT_UNIT_TEST
void ast_destroy_vardec(struct ast_vardec *vardec)
{
  if (vardec == NULL) {
    return;
  }
  if (vardec->next != NULL) {
    ast_destroy_vardec(vardec->next);
  }
  if (vardec->var.name != NULL) {
    free(vardec->var.name);
  }
  free(vardec);
}

void ast_destroy(struct ast *ast)
{
  free(ast->name);
  ast_destroy_vardec(ast->input);
  ast_destroy_vardec(ast->declaration);
}
