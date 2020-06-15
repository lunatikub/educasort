#include <gtest/gtest.h>

extern "C" {
#include <educasort/lexer/lexer.h>
#include "internal.h"
}

class Lexer: public testing::Test
{
protected:

  virtual void SetUp(void);
  virtual void TearDown(void);

  void Test(const std::string &sort, const struct token_list *toks, size_t sz);
  bool TokEq(const std::string &sort, const std::string &str, enum token_type type);

  struct token tok;
};

struct token_list {
  const std::string str;
  enum token_type type;
};

GTEST_API_ int
main(int argc, char **argv)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void Lexer::SetUp(void)
{
  tok.start = 0;
  tok.end = 0;
  tok.line = 1;
  tok.type = TOKEN_NULL;
}

void Lexer::TearDown(void)
{
}

static const char* tokentype2str(enum token_type type)
{
  switch (type) {
    case TOKEN_NULL: return "NULL";
    case TOKEN_STRING: return "string";
    case TOKEN_NUMBER: return "number";
    case TOKEN_OPENING_PARENT: return "(";
    case TOKEN_CLOSING_PARENT: return ")";
    case TOKEN_OPENING_BRACE: return "{";
    case TOKEN_CLOSING_BRACE: return "}";
    case TOKEN_COMA: return ",";
    case TOKEN_DECLARATION: return "declaration";
    case TOKEN_INTEGER: return "integer";
    case TOKEN_END: return "end";
  };
  abort();
}

bool Lexer::TokEq(const std::string &sort, const std::string &str, enum token_type type)
{
  size_t len = (tok.end - tok.start  == 0)
    ? 1 : tok.end - tok.start;

  const std::string s = sort.substr(tok.start, len);

  EXPECT_EQ(s, str) <<
    "Lexer test error: token, " <<
    "expected: " << str << ", " <<
    "result: " << s << std::endl;

  EXPECT_EQ(type, tok.type) <<
    "Lexer test error: token type, " <<
    "expected: " << tokentype2str(type) << ", " <<
    "result: " << tokentype2str(tok.type) << std::endl;

  return s == str && type == tok.type;
}

void Lexer::Test(const std::string &sort, const struct token_list *toks, size_t sz)
{
  const struct token_list *iter;
  for (iter = &toks[0]; iter != &toks[sz]; ++iter) {
    ASSERT_TRUE(lexer_token_fill(sort.c_str(), sort.length(), &tok));
    ASSERT_TRUE(TokEq(sort, iter->str, iter->type)) <<
      "Lexer test error: '" << iter->str << std::endl;
    lexer_token_eat(&tok);
  }
  ASSERT_TRUE(lexer_token_fill(sort.c_str(), sort.length(), &tok));
  ASSERT_EQ(tok.type, TOKEN_END) <<
    "Lexer test error: expected end" << std::endl;
}

#define TOKS_SZ(TOKS) (sizeof(TOKS) / sizeof(TOKS[0]))

/**
 * Test @c is_c function.
 * Allowed char: [_a-zA-z]
 */
TEST_F(Lexer, isChar)
{
  EXPECT_TRUE(is_c('a'));
  EXPECT_TRUE(is_c('Z'));
  EXPECT_TRUE(is_c('_'));
  EXPECT_FALSE(is_c('1'));
  EXPECT_FALSE(is_c('['));
}

/**
 * Test @c is_d function.
 * Allowed char: [0-9]
 */
TEST_F(Lexer, isDigit)
{
  EXPECT_TRUE(is_d('0'));
  EXPECT_TRUE(is_d('7'));
  EXPECT_FALSE(is_d('a'));
  EXPECT_FALSE(is_c('['));
}

/**
 * Test sort lexing.
 */
TEST_F(Lexer, AlgoName)
{
  std::string sort = "FooSort(A array)";

  const static struct token_list toks[] = {
    { "FooSort", TOKEN_STRING },
    { "(", TOKEN_OPENING_PARENT },
    { "A", TOKEN_STRING },
    { "array", TOKEN_STRING },
    { ")", TOKEN_CLOSING_PARENT },
  };

  Test(sort, toks, TOKS_SZ(toks));
}

/**
 * Test declaration lexing.
 */
TEST_F(Lexer, Declaration)
{
  std::string sort = "declaration { i integer, j integer, }";

  const static struct token_list toks[] = {
    { "declaration", TOKEN_DECLARATION },
    { "{", TOKEN_OPENING_BRACE },
    { "i", TOKEN_STRING },
    { "integer", TOKEN_INTEGER },
    { ",", TOKEN_COMA },
    { "j", TOKEN_STRING },
    { "integer", TOKEN_INTEGER },
    { ",", TOKEN_COMA },
    { "}", TOKEN_CLOSING_BRACE },
  };

  Test(sort, toks, TOKS_SZ(toks));
}

/**
 * Test NULL token.
 */
TEST_F(Lexer, TokenNULL)
{
  std::string sort = "- foo";
  ASSERT_FALSE(lexer_token_fill(sort.c_str(), sort.length(), &tok));
  EXPECT_EQ(tok.type, TOKEN_NULL);
}
