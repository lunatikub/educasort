#include <gtest/gtest.h>

extern "C" {
#include <educasort/parser/parser.h>
#include <educasort/visitor/visitor.h>
#include <educasort/visitor/style.h>
}

class Visitor : public testing::Test {
};

GTEST_API_ int main(int argc, char **argv)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST_F(Visitor, Style)
{
  struct visitor_style vs;
  std::string sort;
  struct ast ast;

  sort = "FooSort(A) { declaration{i:integer,j : integer,} }";
  EXPECT_TRUE(parse(&ast, sort.c_str(), sort.length()));

  visitor_style_init(&vs);
  visit(&ast, &vs.visitor);

  ast_destroy(&ast);
}
