#include <iostream>
#include <gtest/gtest.h>

using namespace std;

class example
{
	public:
		int foo()
		{
			return 1;
		}
		
};

class exampleFixture : public testing::Test 
{
	public:
	exampleFixture(){
		testExPtr = new example();
	}
	~exampleFixture()
	{
		delete testExPtr;
	}

	void SetUp(){}
	void TearDown(){}
	
	example* testExPtr;
};

TEST_F(exampleFixture, test1)
{
	ASSERT_EQ(1,testExPtr->foo());
}

TEST_F(exampleFixture, test2)
{
	ASSERT_NE(0,testExPtr->foo());
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
