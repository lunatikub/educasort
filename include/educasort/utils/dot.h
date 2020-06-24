/**
 * @file dot.h
 * @brief API to format dot graph.
 * @author Thomas Joly
 * @version 0.1
 */

#ifndef EDUCASORT_DOT_H__
#define EDUCASORT_DOT_H__

#include <stdbool.h>

#include <educasort/utils/string.h>

/** https://graphviz.org/doc/info/colors.html **/
enum dot_color {
  COLOR_BLACK,
  COLOR_BLUE,
  COLOR_RED,
  COLOR_GREEN,
};

/** https://graphviz.org/doc/info/shapes.html **/
enum dot_shape {
  SHAPE_BOX,
  SHAPE_CIRCLE,
  SHAPE_OCTAGON,
  SHAPE_ELLIPSE,
};

/** Opaque structure to manipulate graph and nodes. */
typedef struct dot_graph dot_graph_t;
typedef struct dot_node dot_node_t;

/**
 * Create a new empty graph.
 *
 * @return The new empty graph allocated.
 */
dot_graph_t *dot_graph_new(void);

/**
 * Destroy a graph.
 *
 * @param graph Graph previously allocated with @c dot_graph_new.
 */
void dot_graph_destroy(dot_graph_t *graph);

/**
 * Create a new empty node and attach it to a graph.
 *
 * @param graph Graph previously allocated with @c dot_graph_new.
 * @param label Label of the node.
 * @param color Color of the node.
 * @param shape Shape of the node.
 * @return The new empty graph allocated.
 */
dot_node_t *dot_node_add(dot_graph_t *graph, const char *label, enum dot_color color,
                         enum dot_shape shape);

/**
 * Add an edge between two nodes.
 *
 * @param graph Graph previously allocated with @c dot_graph_new.
 * @param src Node source.
 * @param dst Node destination.
 * @param label Label of the edge.
 * @param directed True if directed, otherwise false.
 */
void dot_edge_add(dot_graph_t *graph, dot_node_t *src, dot_node_t *dst, const char *label,
                  bool directed);

/**
 * Dump a graph dot into a string.
 *
 * @param graph Graph previously allocated with @c dot_graph_new.
 * @param dot String output.
 */
void dot_dump(struct dot_graph *graph, string_t *dot);

#endif /* !EDUCASORT_DOT_H__ */
