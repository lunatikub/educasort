/**
 * @file style.c
 * @brief Coding style visitor.
 * @author Thomas Joly
 * @version 0.1
 */

#include <stdbool.h>

#include <educasort/visitor/visitor.h>
#include <educasort/visitor/style.h>

#define v_style_get(V) (container_of(V, struct visitor_style, visitor))

#define INDENT_W (2) /* '  ' */

static void indent(string_t *str, int n)
{
  for (int i = 0; i < n; ++i) {
    string_append(str, " ");
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
  indent(vs->algo, vs->indent);
  string_append(vs->algo, "declaration {\n");
  vs->indent += INDENT_W;
  vs->first_vardec = true;
}

static void v_style_declaration_end(const struct visitor *visitor)
{
  struct visitor_style *vs = v_style_get(visitor);
  string_append(vs->algo, "\n");
  vs->indent -= INDENT_W;
  indent(vs->algo, vs->indent);
  string_append(vs->algo, "}\n");
}

static void v_style_vardec(const struct visitor *visitor, const struct ast_vardec *vardec)
{
  struct visitor_style *vs = v_style_get(visitor);

  if (!vs->first_vardec) {
    string_append(vs->algo, ",\n");
  }

  indent(vs->algo, vs->indent);
  string_append(vs->algo, vardec->var.name);
  string_append(vs->algo, ":");
  string_append(vs->algo, get_var_type(vardec->var.type));
  vs->first_vardec = false;
}

static void v_style_sort(const struct visitor *visitor, const struct ast *root)
{
  struct visitor_style *vs = v_style_get(visitor);

  indent(vs->algo, vs->indent);
  string_append(vs->algo, root->name);
  string_append(vs->algo, "() {\n");
  vs->indent += INDENT_W;
}

static void v_style_end(const struct visitor *visitor)
{
  struct visitor_style *vs = v_style_get(visitor);
  string_append(vs->algo, "}");
}

static const struct visitor v_style = {
  .sort = v_style_sort,
  .declaration_start = v_style_declaration_start,
  .declaration_end = v_style_declaration_end,
  .vardec = v_style_vardec,
  .end = v_style_end,
};

void visitor_style_init(struct visitor_style *v)
{
  v->visitor = v_style;
  v->indent = 0;
  v->algo = string_create(128);
}

void visitor_style_clean(struct visitor_style *v)
{
  string_destroy(v->algo);
}
