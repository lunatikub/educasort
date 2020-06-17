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
#define NEXT_NODE(N) (struct ast_node**)&N->node.next
#define CHILD_NODE(N) (struct ast_node**)&N->node.child

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

/**
 * Test syntax errors when parsing the sort section.
 */
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
  EXPECT_TRUE(parse_declaration(NEXT_NODE(node), &tok, sort.c_str(), sort.length()));
  EXPECT_EQ(node->node.child, NULL_NODE);
  EXPECT_EQ(node->node.next, NULL_NODE);
  ast_destroy_node((struct ast_node*)node);
}

/**
 * Test variable declaration parsing.
 */
TEST_F(Parser, Declaration)
{
  std::string sort;
  struct ast_sort *node = (struct ast_sort*)node_new(NODE_SORT, sizeof(*node));
  node->name = strdup("foo");
  struct token tok;

  token_init(&tok);
  sort = "declaration { i:integer, j:integer, }";
  EXPECT_TRUE(parse_declaration(NEXT_NODE(node), &tok, sort.c_str(), sort.length()));
  EXPECT_EQ(node->node.child, NULL_NODE);
  EXPECT_NE(node->node.next, NULL_NODE);
  struct ast_vardec *vardec_node = ast_vardec_get(node->node.next);
  EXPECT_EQ(vardec_node->node.type, NODE_VARDEC);
  EXPECT_EQ(vardec_node->type, VAR_INTEGER);
  EXPECT_EQ(strcmp(vardec_node->name, "i"), 0);
  EXPECT_EQ(vardec_node->node.child, NULL_NODE);
  vardec_node = ast_vardec_get(vardec_node->node.next);
  EXPECT_EQ(vardec_node->node.type, NODE_VARDEC);
  EXPECT_EQ(vardec_node->type, VAR_INTEGER);
  EXPECT_EQ(strcmp(vardec_node->name, "j"), 0);
  EXPECT_EQ(vardec_node->node.child, NULL_NODE);
  ast_destroy_node((struct ast_node*)node);
}

/**
 * Test syntax errors when parsing the declaration.
 */
TEST_F(Parser, DeclarationSyntaxErr)
{
  std::string sort;
  struct token tok;
  struct ast_sort *node;

  // typo 'declaration'
  node = (struct ast_sort*)node_new(NODE_SORT, sizeof(*node));
  node->name = strdup("foo");
  token_init(&tok);
  sort = "bar { i integer, }";
  EXPECT_FALSE(parse_declaration(NEXT_NODE(node), &tok, sort.c_str(), sort.length()));
  ast_destroy_node((struct ast_node*)node);


  // missing ':'
  node = (struct ast_sort*)node_new(NODE_SORT, sizeof(*node));
  node->name = strdup("foo");
  token_init(&tok);
  sort = "declaration { i integer }";
  EXPECT_FALSE(parse_declaration(NEXT_NODE(node), &tok, sort.c_str(), sort.length()));
  ast_destroy_node((struct ast_node*)node);

  // missing type
  node = (struct ast_sort*)node_new(NODE_SORT, sizeof(*node));
  node->name = strdup("foo");
  token_init(&tok);
  sort = "declaration { i, j : integer }";
  EXPECT_FALSE(parse_declaration(NEXT_NODE(node), &tok, sort.c_str(), sort.length()));
  ast_destroy_node((struct ast_node*)node);

  // missing ','
  node = (struct ast_sort*)node_new(NODE_SORT, sizeof(*node));
  node->name = strdup("foo");
  token_init(&tok);
  sort = "declaration { i:integer }";
  EXPECT_FALSE(parse_declaration(NEXT_NODE(node), &tok, sort.c_str(), sort.length()));
  ast_destroy_node((struct ast_node*)node);
}
