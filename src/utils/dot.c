/**
 * @file dot.c
 * @brief API to format dot graph.
 * @author Thomas Joly
 * @version 0.1
 */

#include <stdlib.h>
#include <assert.h>
#include <sys/queue.h>
#include <stdint.h>
#include <string.h>

#include <educasort/utils/dot.h>
#include <educasort/utils/convert.h>

struct dot_edge {
  SLIST_ENTRY(dot_edge) next;
  uint64_t src;
  uint64_t dst;
  char *label;
  bool directed;
};

struct dot_node {
  SLIST_ENTRY(dot_node) next;
  uint64_t id;
  char *label;
  enum dot_color color;
  enum dot_shape shape;
};

struct dot_graph {
  SLIST_HEAD(, dot_node) nodes;
  SLIST_HEAD(, dot_edge) edges;
  uint64_t last_id;
};

static const char *dot_get_color(enum dot_color color)
{
  static const char *colors[] = {
    [COLOR_BLACK] = "black",
    [COLOR_BLUE] = "blue",
    [COLOR_RED] = "red",
  };

  return colors[color];
}

static const char *dot_get_shape(enum dot_shape shape)
{
  static const char *shapes[] = {
    [SHAPE_BOX] = "box",
    [SHAPE_CIRCLE] = "circle",
    [SHAPE_OCTAGON] = "octagon",
  };

  return shapes[shape];
}

struct dot_node *dot_node_add(struct dot_graph *graph, const char *label,
                              enum dot_color color, enum dot_shape shape)
{
  struct dot_node *node = calloc(1, sizeof(*node));
  assert(node != NULL);

  node->id = ++graph->last_id;
  node->label = strdup(label);
  node->color = color;
  node->shape = shape;

  SLIST_INSERT_HEAD(&graph->nodes, node, next);
  return node;
}

void dot_edge_add(dot_graph_t *graph, dot_node_t *src, dot_node_t *dst,
                  const char *label, bool directed)
{
  struct dot_edge *edge = calloc(1, sizeof(*edge));
  assert(edge != NULL);

  edge->src = src->id;
  edge->dst = dst->id;
  if (label) {
    edge->label = strdup(label);
  }
  edge->directed = directed;

  SLIST_INSERT_HEAD(&graph->edges, edge, next);
}

struct dot_graph *dot_graph_new(void)
{
  struct dot_graph *graph = calloc(1, sizeof(*graph));
  assert(graph != NULL);
  SLIST_INIT(&graph->nodes);
  SLIST_INIT(&graph->edges);
  return graph;
}

void dot_graph_destroy(struct dot_graph *graph)
{
  while (!SLIST_EMPTY(&graph->nodes)) {
    struct dot_node *node = SLIST_FIRST(&graph->nodes);
    SLIST_REMOVE_HEAD(&graph->nodes, next);
    free(node->label);
    free(node);
  }
  while (!SLIST_EMPTY(&graph->edges)) {
    struct dot_edge *edge = SLIST_FIRST(&graph->edges);
    SLIST_REMOVE_HEAD(&graph->edges, next);
    if (edge->label) {
      free(edge);
    }
    free(edge);
  }
  free(graph);
}
#define LEN_ID (128)

static void dot_dump_node(struct dot_node *node, string_t *dot)
{
  char id[LEN_ID];
  u64tostr(node->id, id, LEN_ID);

  string_append(dot, "  ");
  string_append(dot, id);
  string_append(dot, " [shape=");
  string_append(dot, dot_get_shape(node->shape));
  string_append(dot, ", color=");
  string_append(dot, dot_get_color(node->color));
  string_append(dot, ", label=\"");
  string_append(dot, node->label);
  string_append(dot, "\"]\n");
}

static void dot_dump_edge(struct dot_edge *edge, string_t *dot)
{
  char src[LEN_ID];
  char dst[LEN_ID];

  u64tostr(edge->src, src, LEN_ID);
  u64tostr(edge->dst, dst, LEN_ID);

  string_append(dot, "  ");
  string_append(dot, src);
  if (edge->directed) {
    string_append(dot, " -> ");
  } else {
    string_append(dot, " -- ");
  }
  string_append(dot, dst);
  if (edge->label) {
    string_append(dot, " [ label=\"");
    string_append(dot, edge->label);
    string_append(dot, "\"]");
  }
  string_append(dot, "\n");
}

void dot_dump(struct dot_graph *graph, string_t *dot)
{
  string_append(dot, "digraph {\n");

  struct dot_node *node;
  SLIST_FOREACH(node, &graph->nodes, next) {
    dot_dump_node(node, dot);
  }

  struct dot_edge *edge;
  SLIST_FOREACH(edge, &graph->edges, next) {
    dot_dump_edge(edge, dot);
  }

  string_append(dot, "}");
}
