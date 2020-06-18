/**
 * @file style.c
 * @brief Coding style visitor.
 * @author Thomas Joly
 * @version 0.1
 */

#include <stdbool.h>

#include <educasort/visitor/visitor.h>
#include <educasort/visitor/style.h>

#include <stdio.h> // TO DEL

#define v_style_get(V) (container_of(V, struct visitor_style, visitor))

#define INDENT_W (2) /* '  ' */

static void indent(int n)
{
  for (int i = 0; i < n; ++i) {
    fprintf(stderr, " ");
  }
}

static const char *get_var_type(enum var_type type)
{
  switch (type) {
    case VAR_INTEGER: return "integer";
  };
  return NULL;
}

static void v_style_declaration_start(const struct visitor *visitor)
{
  struct visitor_style *vs = v_style_get(visitor);
  indent(vs->indent);
  fprintf(stderr, "declaration {\n");
  vs->indent += INDENT_W;
}

static void v_style_declaration_end(const struct visitor *visitor)
{
  struct visitor_style *vs = v_style_get(visitor);
  vs->indent -= INDENT_W;
  indent(vs->indent);
  fprintf(stderr, "}\n");
}

static void v_style_vardec(const struct visitor *visitor, const struct ast_vardec *vardec_node)
{
  struct visitor_style *vs = v_style_get(visitor);

  indent(vs->indent);
  fprintf(stderr, "%s:%s,\n", vardec_node->name, get_var_type(vardec_node->type));
}

static void v_style_sort(const struct visitor *visitor, const struct ast_sort *sort_node)
{
  struct visitor_style *vs = v_style_get(visitor);

  indent(vs->indent);
  fprintf(stderr, "%s(A) {\n", sort_node->name);
  vs->indent += INDENT_W;
}

static void v_style_start(const struct visitor *visitor)
{
  struct visitor_style *vs = v_style_get(visitor);
  vs->indent = 0;
}

static void v_style_end(const struct visitor *visitor)
{
  (void)visitor;
  fprintf(stderr, "}\n");
}

static const struct visitor v_style = {
  .sort = v_style_sort,
  .declaration_start = v_style_declaration_start,
  .declaration_end = v_style_declaration_end,
  .vardec = v_style_vardec,
  .start = v_style_start,
  .end = v_style_end,
};

void visitor_style_init(struct visitor_style *v)
{
  v->visitor = v_style;
}
