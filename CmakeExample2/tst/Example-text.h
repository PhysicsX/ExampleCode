#include <gtest/gtest.h>
#include "Example.h"


class TestBase : public ::testing::Test
{
public:
	TestBase(void);
	virtual ~TestBase(void);
	static void SetUpTestCase();
	static void TearDownTestCase();
	virtual void SetUp(void);
	virtual void TearDown(void);

public:
	static int mArgc;
	static char** mArgs;

	static Example* pSC;

};