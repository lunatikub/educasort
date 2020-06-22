#include <gtest/gtest.h>

extern "C" {
#include "internal.h"
#include <educasort/lexer/lexer.h>
}

class Lexer : public testing::Test {
protected:
  virtual void SetUp(void);
  virtual void TearDown(void);

  bool TokEq(const std::string &sort, const std::string &str, enum token_type type);

  struct token tok;
};

struct token_list {
  const std::string str;
  enum token_type type;
};

GTEST_API_ int main(int argc, char **argv)
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

void Lexer::TearDown(void) {}

static const char *tokentype2str(enum token_type type)
{
  switch (type) {
    case TOKEN_NULL: return "NULL";
    case TOKEN_IDENTIFIER: return "identifier";
    case TOKEN_NUMBER: return "number";
    case TOKEN_OPENING_PARENT: return "(";
    case TOKEN_CLOSING_PARENT: return ")";
    case TOKEN_OPENING_BRACE: return "{";
    case TOKEN_CLOSING_BRACE: return "}";
    case TOKEN_COMMA: return ",";
    case TOKEN_COLON: return ":";
    case TOKEN_PLUS: return "+";
    case TOKEN_MINUS: return "-";
    case TOKEN_SLASH: return "/";
    case TOKEN_ASTERISK: return "*";
    case TOKEN_DECLARATION: return "declaration";
    case TOKEN_INTEGER: return "integer";
    case TOKEN_END: return "end";
  };
  abort();
}

bool Lexer::TokEq(const std::string &sort, const std::string &str, enum token_type type)
{
  size_t len = (tok.end - tok.start == 0) ? 1 : tok.end - tok.start;

  const std::string s = sort.substr(tok.start, len);

  EXPECT_EQ(s, str) << "Lexer test error: token, "
                    << "expected: " << str << ", "
                    << "result: " << s << std::endl;

  EXPECT_EQ(type, tok.type) << "Lexer test error: token type, "
                            << "expected: " << tokentype2str(type) << ", "
                            << "result: " << tokentype2str(tok.type) << std::endl;

  return s == str && type == tok.type;
}

#define TOKS_SZ(TOKS) (sizeof(TOKS) / sizeof(TOKS[0]))

TEST_F(Lexer, isChar)
{
  EXPECT_TRUE(is_c('a'));
  EXPECT_TRUE(is_c('Z'));
  EXPECT_TRUE(is_c('_'));
  EXPECT_FALSE(is_c('1'));
  EXPECT_FALSE(is_c('['));
}

TEST_F(Lexer, isDigit)
{
  EXPECT_TRUE(is_d('0'));
  EXPECT_TRUE(is_d('7'));
  EXPECT_FALSE(is_d('a'));
  EXPECT_FALSE(is_c('['));
}

TEST_F(Lexer, AllowedToken)
{
  std::string algo = " FooSort (  A ) +-/* Bar : integer , : { }} , declaration";

  const static struct token_list toks[] = {
    { "FooSort", TOKEN_IDENTIFIER },
    { "(", TOKEN_OPENING_PARENT },
    { "A", TOKEN_IDENTIFIER },
    { ")", TOKEN_CLOSING_PARENT },
    { "+", TOKEN_PLUS },
    { "-", TOKEN_MINUS },
    { "/", TOKEN_SLASH },
    { "*", TOKEN_ASTERISK },
    { "Bar", TOKEN_IDENTIFIER },
    { ":", TOKEN_COLON },
    { "integer", TOKEN_INTEGER },
    { ",", TOKEN_COMMA },
    { ":", TOKEN_COLON },
    { "{", TOKEN_OPENING_BRACE },
    { "}", TOKEN_CLOSING_BRACE },
    { "}", TOKEN_CLOSING_BRACE },
    { ",", TOKEN_COMMA },
    { "declaration", TOKEN_DECLARATION },
  };

  const struct token_list *iter;
  for (iter = &toks[0]; iter != &toks[TOKS_SZ(toks)]; ++iter) {
    ASSERT_TRUE(lexer_token_fill(algo.c_str(), algo.length(), &tok));
    ASSERT_TRUE(TokEq(algo, iter->str, iter->type))
      << "Lexer test error: '" << iter->str << std::endl;
    lexer_token_eat(&tok);
  }
  ASSERT_TRUE(lexer_token_fill(algo.c_str(), algo.length(), &tok));
  ASSERT_EQ(tok.type, TOKEN_END) << "Lexer test error: expected end" << std::endl;
}

TEST_F(Lexer, TokenNULL)
{
  std::string algo;

  algo = "@";
  ASSERT_FALSE(lexer_token_fill(algo.c_str(), algo.length(), &tok));
  EXPECT_EQ(tok.type, TOKEN_NULL);
}
