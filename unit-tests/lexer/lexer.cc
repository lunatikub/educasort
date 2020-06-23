#include <gtest/gtest.h>

extern "C" {
#include "internal.h"
#include <educasort/lexer/lexer.h>
}

class Lexer : public testing::Test {
protected:
  virtual void SetUp(void);
  virtual void TearDown(void);
};

GTEST_API_ int main(int argc, char **argv)
{
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void Lexer::SetUp(void) {}

void Lexer::TearDown(void) {}

static const char *type2str(enum token_type type)
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
    case TOKEN_TYPE_INTEGER: return "integer";
    case TOKEN_END: return "end";
  };
  abort();
}

#define ARRAY_SZ(TOKS) (sizeof(TOKS) / sizeof(TOKS[0]))

TEST_F(Lexer, Tokenizer)
{
  std::string algo = "FooSort () +-/* Bar : integer , : { }} , declaration";

  token_t *tok = tokenizer(algo.c_str(), algo.length());
  ASSERT_NE(tok, nullptr);

  const static enum token_type expected_type[] = {
    TOKEN_IDENTIFIER,    TOKEN_OPENING_PARENT, TOKEN_CLOSING_PARENT, TOKEN_PLUS,
    TOKEN_MINUS,         TOKEN_SLASH,          TOKEN_ASTERISK,       TOKEN_IDENTIFIER,
    TOKEN_COLON,         TOKEN_TYPE_INTEGER,   TOKEN_COMMA,          TOKEN_COLON,
    TOKEN_OPENING_BRACE, TOKEN_CLOSING_BRACE,  TOKEN_CLOSING_BRACE,  TOKEN_COMMA,
    TOKEN_DECLARATION,
  };

  for (enum token_type const *type = &expected_type[0];
       type != &expected_type[ARRAY_SZ(expected_type)]; ++type) {
    EXPECT_EQ(*type, token_type(tok)) << "expected type: " << type2str(*type)
                                      << ", unexpected: " << type2str(token_type(tok)) << std::endl;
    ASSERT_NE(tok = token_next(tok), nullptr);
  }
  // No more token
  EXPECT_EQ(token_next(tok), nullptr);
  EXPECT_EQ(token_next(tok), nullptr);

  token_destroy(tok);
}

TEST_F(Lexer, TokenNULL)
{
  std::string algo;
  struct token *tok;

  algo = "~";
  tok = tokenizer(algo.c_str(), algo.length());
  ASSERT_EQ(tok, nullptr);

  algo = "(+~";
  tok = tokenizer(algo.c_str(), algo.length());
  ASSERT_EQ(tok, nullptr);
}
