#include <gtest/gtest.h>

extern "C" {
#include <educasort/parser/parser.h>
}

class Parser: public testing::Test
{
protected:

  virtual void SetUp(void);
  virtual void TearDown(void);
};

GTEST_API_ int
main(int argc, char **argv)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void Parser::SetUp(void)
{
}

void Parser::TearDown(void)
{
}

/**
 * Test sort parsing.
 */
TEST_F(Parser, AlgoSort)
{
  std::string sort = "FooSort(A) { ";
  struct ast ast;

  EXPECT_TRUE(parse(&ast, sort.c_str(), sort.length()));
}
