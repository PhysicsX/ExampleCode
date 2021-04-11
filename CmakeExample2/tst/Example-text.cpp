#include "Example-text.h"

int TestBase::mArgc = 0;
char** TestBase::mArgs = NULL;

Example* TestBase::pSC = NULL;

TestBase::TestBase(void)
{

}

TestBase::~TestBase(void)
{

}

void TestBase::SetUpTestCase()
{
	std::cout << "Set up test cases." << std::endl;

	if ( pSC != NULL )
	{
		delete pSC;
	}

	pSC = new Example;
}

void TestBase::TearDownTestCase()
{
	std::cout << "Tear down test cases." << std::endl;

	delete pSC; pSC = NULL;
}

void TestBase::SetUp(void)
{

}

void TestBase::TearDown(void)
{

}

TEST_F(TestBase, tmp)
{
    Example a;
    int tmp = pSC->foo();
    EXPECT_EQ(tmp,1);
}