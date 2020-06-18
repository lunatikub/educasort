#include <gtest/gtest.h>

extern "C" {
#include <educasort/utils/string.h>
#include "internal.h"
}

class String : public testing::Test {
};

TEST_F(String, Append)
{
  string_t *s = string_create(2);

  EXPECT_EQ(string_len(s), 0u);
  EXPECT_EQ(string_capa(s), 2u);

  string_append(s, "foo");
  EXPECT_EQ(strcmp("foo", string_get(s)), 0);
  EXPECT_EQ(string_len(s), 3u);
  EXPECT_EQ(string_capa(s), 4u);

  string_append(s, "0");
  EXPECT_EQ(strcmp("foo0", string_get(s)), 0);
  EXPECT_EQ(string_len(s), 4u);
  EXPECT_EQ(string_capa(s), 4u);

  string_append(s, "123456789");
  EXPECT_EQ(strcmp("foo0123456789", string_get(s)), 0);
  EXPECT_EQ(string_len(s), 13u);
  EXPECT_EQ(string_capa(s), 16u);

  string_destroy(s);
}
