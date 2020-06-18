#include <gtest/gtest.h>

extern "C" {
#include <educasort/utils/file.h>
}

class File : public testing::Test {
};

TEST_F(File, FileToBuf)
{
  std::string expected = "\
Foo\n\
Bar\n\
Foo1\n\
Bar1\n\
Foo2\n\
Bar2\n";

  size_t len = 0;
  char *buf = filetobuf("./unit-tests/utils/test.txt", &len);
  ASSERT_NE(buf, (char *)NULL);
  EXPECT_EQ(len, strlen(expected.c_str()));
  EXPECT_TRUE(strncmp(expected.c_str(), buf, len) == 0);
  free(buf);
}

TEST_F(File, BufToFile)
{
  std::string to_write = "\
Foo\n\
Bar\n\
Foo1\n\
Bar1";

  const char *file_path = "/tmp/file_test.txt";

  EXPECT_TRUE(buftofile(file_path, to_write.c_str(), to_write.length()));

  size_t len;
  char *buf = filetobuf(file_path, &len);
  ASSERT_NE(buf, (char *)NULL);

  EXPECT_EQ(len, to_write.length());
  EXPECT_TRUE(strncmp(to_write.c_str(), buf, len) == 0);
  free(buf);
}
