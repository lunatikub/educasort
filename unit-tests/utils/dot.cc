#include <gtest/gtest.h>

extern "C" {
#include <educasort/utils/dot.h>
#include <educasort/utils/file.h>
#include <educasort/utils/string.h>
}

class Dot : public testing::Test {
};

TEST_F(Dot, SimpleGraph)
{
  dot_graph_t *g = dot_graph_new();

  dot_node_t *n1 = dot_node_add(g, "+", COLOR_RED, SHAPE_BOX);
  dot_node_t *n2 = dot_node_add(g, "1", COLOR_BLACK, SHAPE_CIRCLE);
  dot_node_t *n3 = dot_node_add(g, "2", COLOR_BLACK, SHAPE_CIRCLE);

  dot_edge_add(g, n1, n2, NULL, true);
  dot_edge_add(g, n1, n3, NULL, true);

  std::string expected = "\
digraph {\n\
  3 [shape=circle, color=black, label=\"2\"]\n\
  2 [shape=circle, color=black, label=\"1\"]\n\
  1 [shape=box, color=red, label=\"+\"]\n\
  1 -> 3\n\
  1 -> 2\n\
}";

  string_t *s = string_create(128);
  dot_dump(g, s);

  EXPECT_EQ(expected.length(), string_len(s));
  EXPECT_EQ(strcmp(expected.c_str(), string_get(s)), 0);

  string_destroy(s);
  dot_graph_destroy(g);
}
