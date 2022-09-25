#include <iostream>
#include <gtest/gtest.h>
#include "dummy.hpp"
#include "foo_if.hpp"
#include "foo.hpp"
#include "mock_foo.hpp"

class myTestFixture: public testing::Test { 
public: 
   myTestFixture( ) { 
    // initialization code here
    // This function will be called again for each test of beginning
	// testDummy will be null for each test
    std::cout<<"testDummy is null "<<(mTestDummy == nullptr)<<std::endl;
	mTestDummy = std::make_unique<dummy>(mMockFoo);
   } 

   void SetUp( ) { 
       // code here will execute just before the test ensues 
   }

   void TearDown( ) { 
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
   }

   ~myTestFixture( )  { 
       // cleanup any pending stuff, but no exceptions allowed
   }

   mockFoo mMockFoo;
   std::unique_ptr<dummy> mTestDummy;
   // put in any custom data members that you need 
};


TEST_F (myTestFixture, TestDummyInt) { 

	std::string testString {"testString"};
	EXPECT_CALL(mMockFoo, fooInt(testing::_)).Times(1).WillOnce(testing::Return(testString.size()));
	int result = mTestDummy->dummyInt(testString);
	
	ASSERT_EQ(result,testString.size());
}

TEST_F (myTestFixture, TestDummyStr) { 
	std::string testString;
	std::string returnStr {"testString"};
	EXPECT_CALL(mMockFoo, fooStr(testing::_)).WillOnce(testing::SetArgReferee<0>(returnStr));
	mTestDummy->dummyStr(testString);
	
	ASSERT_EQ(testString,returnStr);
}

TEST_F (myTestFixture, UnitTest2) { 
   ASSERT_EQ(1,1);
}

ACTION(throwError)
{
    std::cout << "ERROR!\n";
    throw std::runtime_error("ERROR_TEST");
}

TEST_F (myTestFixture, ThrowTest) { 
    
    EXPECT_CALL(mMockFoo, fooThrow()).WillOnce(throwError());
    ASSERT_THROW(mTestDummy->dummyThrow(), std::runtime_error);

}


void throwFunction()
{
    std::cout << "ERROR!\n";
    throw std::runtime_error("ERROR_TEST");
}

TEST_F (myTestFixture, ThrowTest2) { 

    EXPECT_CALL(mMockFoo, fooThrow()).WillOnce(testing::Throw(std::runtime_error("ERROR_TEST")));
    ASSERT_THROW(mTestDummy->dummyThrow(), std::runtime_error);

    EXPECT_CALL(mMockFoo, fooThrow()).WillOnce(testing::Invoke([](){
            std::cout << "ERROR!\n";
    throw std::runtime_error("ERROR_TEST");
    }));

    ASSERT_THROW(mTestDummy->dummyThrow(), std::runtime_error);

    EXPECT_CALL(mMockFoo, fooThrow()).WillOnce(testing::Invoke(throwFunction));
    ASSERT_THROW(mTestDummy->dummyThrow(), std::runtime_error);
}

TEST_F (myTestFixture, TestCallback) { 

    testing::MockFunction<void(void)> testFunc;
    // std::function is not ==, that is why _ is used. Call can be checked.
    EXPECT_CALL(mMockFoo, callbackMethod(testing::_)).Times(1) 
    .WillOnce(testing::InvokeArgument<0>());
    EXPECT_CALL(testFunc, Call());
    
    mTestDummy->dummyCallback(testFunc.AsStdFunction());
    
}