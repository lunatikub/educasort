#include <gtest/gtest.h>

extern "C" {
#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>
#include "internal.h"
#include "node.h"
#include "token.h"
}

class Parser: public testing::Test
{
};

GTEST_API_ int
main(int argc, char **argv)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

#define NULL_NODE ((struct ast_node*)NULL)

/**
 * Test empty sort algo parsing.
 */
TEST_F(Parser, EmptySort)
{
  std::string sort;
  struct ast ast;

  sort = "FooSort(A) { }";
  EXPECT_TRUE(parse(&ast, sort.c_str(), sort.length()));
  EXPECT_EQ(ast.root.type, NODE_ROOT);
  EXPECT_EQ(ast.root.next, NULL_NODE);
  EXPECT_NE(ast.root.child, NULL_NODE);
  struct ast_sort *sort_node = ast_sort_get(ast.root.child);
  EXPECT_EQ(sort_node->node.next, NULL_NODE);
  EXPECT_EQ(sort_node->node.child, NULL_NODE);
  EXPECT_EQ(strcmp(sort_node->name, "FooSort"), 0);
  ast_destroy(&ast);
}

TEST_F(Parser, SortSyntaxErr)
{
  std::string sort;
  struct ast ast;

  // missing opening brace
  sort = "FooSort(A)";
  EXPECT_FALSE(parse(&ast, sort.c_str(), sort.length()));
  ast_destroy(&ast);

  // missing closing brace
  sort = "FooSort(A) { ";
  EXPECT_FALSE(parse(&ast, sort.c_str(), sort.length()));
  ast_destroy(&ast);
}

/**
 * Test empty declaration parsing.
 */
TEST_F(Parser, EmptyDeclaration)
{
  std::string sort;
  struct ast_sort *node = (struct ast_sort*)node_new(NODE_SORT, sizeof(*node));
  node->name = strdup("foo");
  struct token tok;

  token_init(&tok);
  sort = "declaration { }";
  EXPECT_TRUE(parse_declaration((struct ast_node*)node, &tok, sort.c_str(), sort.length()));
  ast_destroy_node((struct ast_node*)node);
}
