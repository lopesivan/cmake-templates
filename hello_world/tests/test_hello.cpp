#include "gtest/gtest.h"
#include "hello.hpp"

TEST(HelloTest, ReturnsCorrectMessage) {
EXPECT_EQ(get_hello_message(), "Hello, World!");
}
