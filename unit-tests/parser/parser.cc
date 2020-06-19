#include <gtest/gtest.h>

extern "C" {
#include "internal.h"
#include "token.h"
#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>
#include <educasort/parser/ast.h>
}

class Parser : public testing::Test {
protected:
  virtual void SetUp(void);
  virtual void TearDown(void);

  std::string algo;
  struct ast ast;
  struct token tok;
  struct ast_vardec *vardec;
};

GTEST_API_ int main(int argc, char **argv)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void Parser::SetUp(void)
{
  token_init(&tok);
  memset(&ast, 0, sizeof(struct ast));
  vardec = NULL;
}

void Parser::TearDown(void)
{
  ast_destroy(&ast);
}

#define VARDEC_NULL ((struct ast_vardec *)NULL)

TEST_F(Parser, ListVarDec)
{
  algo = "i:integer, j:integer";

  EXPECT_TRUE(parse_list_vardec(&vardec, &tok, algo.c_str(), algo.length()));

  EXPECT_EQ(strcmp(vardec->name, "i"), 0);
  EXPECT_EQ(vardec->type, VAR_INTEGER);
  ASSERT_NE(vardec->next, nullptr);
  struct ast_vardec *next = vardec->next;
  EXPECT_EQ(strcmp(next->name, "j"), 0);
  EXPECT_EQ(next->type, VAR_INTEGER);

  ast_destroy_vardec(vardec);

}

TEST_F(Parser, MissingColonVardec)
{
  algo = "i integer";
  EXPECT_FALSE(parse_list_vardec(&vardec, &tok, algo.c_str(), algo.length()));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, MissingTypeVardec)
{
  algo = "i, j : integer";
  EXPECT_FALSE(parse_list_vardec(&vardec, &tok, algo.c_str(), algo.length()));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, MissingCommaVardec)
{
  algo = "i:integer j:integer";
  EXPECT_FALSE(parse_list_vardec(&vardec, &tok, algo.c_str(), algo.length()));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, EmptySort)
{
  algo = "FooSort() { }";
  EXPECT_TRUE(parse(&ast, algo.c_str(), algo.length()));

  EXPECT_EQ(ast.declaration, VARDEC_NULL);
  EXPECT_EQ(ast.input, VARDEC_NULL);
  EXPECT_EQ(strcmp(ast.name, "FooSort"), 0);
}

TEST_F(Parser, SortInput)
{
  algo = "bar(foo:integer, foo_:integer) { }";
  EXPECT_TRUE(parse(&ast, algo.c_str(), algo.length()));

  ASSERT_NE(ast.input, nullptr);
  EXPECT_EQ(strcmp(ast.name, "bar"), 0);
  struct ast_vardec *first = ast.input;
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(strcmp(first->name, "foo"), 0);
  EXPECT_EQ(first->type, VAR_INTEGER);
  ASSERT_NE(first->next, nullptr);
  struct ast_vardec *second = first->next;
  EXPECT_EQ(strcmp(second->name, "foo_"), 0);
  EXPECT_EQ(second->type, VAR_INTEGER);
  EXPECT_EQ(second->next, nullptr);
}

TEST_F(Parser, MissingOpeningBraceSort)
{
  algo = "FooSort()";
  EXPECT_FALSE(parse(&ast, algo.c_str(), algo.length()));
}

TEST_F(Parser, MissingClosingBraceSort)
{
  algo = "FooSort() { ";
  EXPECT_FALSE(parse(&ast, algo.c_str(), algo.length()));
}

TEST_F(Parser, EmptyDeclaration)
{

  algo = "declaration { }";
  EXPECT_TRUE(parse_declaration(&vardec, &tok, algo.c_str(), algo.length()));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, Declaration)
{
  algo = "declaration { i:integer, j:integer }";

  EXPECT_TRUE(parse_declaration(&vardec, &tok, algo.c_str(), algo.length()));

  EXPECT_EQ(strcmp(vardec->name, "i"), 0);
  EXPECT_EQ(vardec->type, VAR_INTEGER);
  ASSERT_NE(vardec->next, nullptr);
  struct ast_vardec *next = vardec->next;
  EXPECT_EQ(strcmp(next->name, "j"), 0);
  EXPECT_EQ(next->type, VAR_INTEGER);
  EXPECT_EQ(next->next, nullptr);

  ast_destroy_vardec(vardec);
}

TEST_F(Parser, TypoDeclaration)
{
  algo = "bar { }";
  EXPECT_FALSE(parse_declaration(&vardec, &tok, algo.c_str(), algo.length()));
  ast_destroy_vardec(vardec);
}
