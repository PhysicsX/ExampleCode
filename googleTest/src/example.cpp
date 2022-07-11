#include <iostream>
#include <gtest/gtest.h>
// g++ example.cpp googletest/build/lib/libgtest.a googletest/build/lib/libgtest_main.a -lpthread -I googletest/googletest/include/
using namespace std;

TEST(TestName, test1)
{
	ASSERT_EQ(1, 1);
}

// int main(int argc, char **argv)
// {
// 	testing::InitGoogleTest(&argc, argv);
// 	return RUN_ALL_TESTS();
// }
