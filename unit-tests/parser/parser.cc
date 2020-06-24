#include <gtest/gtest.h>

extern "C" {
#include <educasort/lexer/lexer.h>
#include <educasort/parser/parser.h>
#include <educasort/parser/ast.h>
#include "parser_internal.h"
}

class Parser : public testing::Test {
protected:
  virtual void SetUp(void);
  virtual void TearDown(void);

  std::string algo;
  struct ast ast;
  token_t *tok;
  struct ast_vardec *vardec;
  struct ast_expr *expr;
};

GTEST_API_ int main(int argc, char **argv)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void Parser::SetUp(void)
{
  memset(&ast, 0, sizeof(struct ast));
  vardec = NULL;
  tok = NULL;
}

void Parser::TearDown(void)
{
  token_destroy(tok);
  ast_destroy(&ast);
}

#define VARDEC_NULL ((struct ast_vardec *)NULL)

TEST_F(Parser, ListVarDec)
{
  algo = "i:integer, j:integer";
  tok = tokenizer(algo.c_str(), algo.length());

  EXPECT_TRUE(parse_list_vardec(&vardec, &tok));

  EXPECT_EQ(strcmp(vardec->var.name, "i"), 0);
  EXPECT_EQ(vardec->var.type, VAR_INTEGER);
  ASSERT_NE(vardec->next, nullptr);
  struct ast_vardec *next = vardec->next;
  EXPECT_EQ(strcmp(next->var.name, "j"), 0);
  EXPECT_EQ(next->var.type, VAR_INTEGER);

  ast_destroy_vardec(vardec);
}

TEST_F(Parser, MissingColonVardec)
{
  algo = "i integer";
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_FALSE(parse_list_vardec(&vardec, &tok));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, MissingTypeVardec)
{
  algo = "i, j : integer";
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_FALSE(parse_list_vardec(&vardec, &tok));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, MissingCommaVardec)
{
  algo = "i:integer j:integer";
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_FALSE(parse_list_vardec(&vardec, &tok));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, EmptySort)
{
  algo = "FooSort() { }";
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_TRUE(parse(&ast, algo.c_str(), algo.length()));
  EXPECT_EQ(ast.declaration, VARDEC_NULL);
  EXPECT_EQ(ast.input, VARDEC_NULL);
  EXPECT_EQ(strcmp(ast.name, "FooSort"), 0);
}

TEST_F(Parser, SortInput)
{
  algo = "bar(foo:integer, foo_:integer) { }";
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_TRUE(parse(&ast, algo.c_str(), algo.length()));
  ASSERT_NE(ast.input, nullptr);
  EXPECT_EQ(strcmp(ast.name, "bar"), 0);
  struct ast_vardec *first = ast.input;
  ASSERT_NE(first, nullptr);
  EXPECT_EQ(strcmp(first->var.name, "foo"), 0);
  EXPECT_EQ(first->var.type, VAR_INTEGER);
  ASSERT_NE(first->next, nullptr);
  struct ast_vardec *second = first->next;
  EXPECT_EQ(strcmp(second->var.name, "foo_"), 0);
  EXPECT_EQ(second->var.type, VAR_INTEGER);
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
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_TRUE(parse_declaration(&vardec, &tok));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, Declaration)
{
  algo = "declaration { i:integer, j:integer }";
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_TRUE(parse_declaration(&vardec, &tok));
  EXPECT_EQ(strcmp(vardec->var.name, "i"), 0);
  EXPECT_EQ(vardec->var.type, VAR_INTEGER);
  ASSERT_NE(vardec->next, nullptr);
  struct ast_vardec *next = vardec->next;
  EXPECT_EQ(strcmp(next->var.name, "j"), 0);
  EXPECT_EQ(next->var.type, VAR_INTEGER);
  EXPECT_EQ(next->next, nullptr);
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, TypoDeclaration)
{
  algo = "bar { }";
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_FALSE(parse_declaration(&vardec, &tok));
  ast_destroy_vardec(vardec);
}

TEST_F(Parser, Expr)
{
  algo = "1 + 2";
  tok = tokenizer(algo.c_str(), algo.length());
  EXPECT_TRUE(parse_expr(&expr, &tok));
}
