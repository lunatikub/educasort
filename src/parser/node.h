/**
 * @file node.h
 * @brief Utilities to manipulate node.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef NODE_H__
#define NODE_H__

#include <assert.h>
#include <stdlib.h>

#include <educasort/parser/ast.h>

static inline void node_set(struct ast_node **dst, void *src)
{
  *dst = (struct ast_node *)src;
}

static inline void node_init(struct ast_node *node, enum node_type type)
{
  node->next = NULL;
  node->child = NULL;
  node->type = type;
}

static inline void *node_new(enum node_type type, size_t sz)
{
  struct ast_node *node = (struct ast_node *)calloc(1, sz);
  assert(node != NULL);
  node_init(node, type);
  return node;
}

#endif /* !NODE_H__ */
