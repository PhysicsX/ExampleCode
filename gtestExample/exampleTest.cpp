#include <iostream>
#include <gtest/gtest.h>
#include "example.cpp"

using namespace std;
// g++ -Wall -g -pthread exampleTest.cpp example.cpp -lgtest_main  -lgtest -lpthread -o test
// test fixture
class ExampleTest : public testing::Test
{
    protected:
    Example *ex;
    void SetUp()
    {
        ex = new Example;
        cout<<"Created"<<std::endl;
    }

    void TearDown()
    {
        delete ex;
        cout<<"Deleted"<<std::endl;
    }
};

TEST_F(ExampleTest, test3)
{
    ex->increase(100);
    EXPECT_EQ(100,ex->ctr);
}

TEST(Example, test1)
{
    Example inst;
    inst.increase(100);
    EXPECT_EQ(100, inst.ctr);
}

TEST(Example, test2)
{
    Example inst;
    inst.increase(100);
    ASSERT_EQ(500, inst.ctr);

    inst.decrease(50);
    EXPECT_EQ(100, inst.ctr);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}