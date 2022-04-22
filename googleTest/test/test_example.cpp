#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>
#include "dummy.hpp"
#include "foo_if.hpp"
#include "foo.hpp"
#include "mock_foo.hpp"

class myTestFixture1: public ::testing::Test { 
public: 
   myTestFixture1( ) { 
       // initialization code here
	std::cout<<"testDummy is null "<<(testDummy == nullptr)<<std::endl;
	//foo fooTest;	
	//mockFoo fooTest;	
	testDummy = std::make_unique<dummy>(fooTest);
   } 

   void SetUp( ) { 
       // code here will execute just before the test ensues 
   }

   void TearDown( ) { 
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
   }

   ~myTestFixture1( )  { 
       // cleanup any pending stuff, but no exceptions allowed
   }
   mockFoo fooTest;
   std::unique_ptr<dummy> testDummy;
   // put in any custom data members that you need 
};



TEST_F (myTestFixture1, TestDummyStr) { 
	std::string testString;
	std::string returnStr {"testString"};
	EXPECT_CALL(fooTest, fooStr(::testing::_)).WillOnce(::testing::SetArgReferee<0>(returnStr));
	testDummy->dummyStr(testString);
	
	ASSERT_EQ(testString,returnStr);
}

TEST_F (myTestFixture1, UnitTest2) { 
   ASSERT_EQ(1,1);
}

ACTION(throwError)
{
    std::cout << "ERROR!\n";
    throw std::runtime_error("ERROR_TEST");
}

TEST_F (myTestFixture1, ThrowTest) { 

    EXPECT_CALL(fooTest, fooThrow()).WillOnce(throwError());
    ASSERT_THROW(testDummy->dummyThrow(), std::runtime_error);
}


void throwFunction()
{
    std::cout << "ERROR!\n";
    throw std::runtime_error("ERROR_TEST");
}

TEST_F (myTestFixture1, ThrowTest2) { 

    EXPECT_CALL(fooTest, fooThrow()).WillOnce(testing::Throw(std::runtime_error("ERROR_TEST")));
    ASSERT_THROW(testDummy->dummyThrow(), std::runtime_error);

    EXPECT_CALL(fooTest, fooThrow()).WillOnce(testing::Invoke([](){
            std::cout << "ERROR!\n";
    throw std::runtime_error("ERROR_TEST");
    }));
    ASSERT_THROW(testDummy->dummyThrow(), std::runtime_error);

    EXPECT_CALL(fooTest, fooThrow()).WillOnce(testing::Invoke(throwFunction));
    ASSERT_THROW(testDummy->dummyThrow(), std::runtime_error);
}


TEST_F (myTestFixture1, TestCallback) { 

    testing::MockFunction<void(void)> testFunc;
    // std::function is not ==, that is why _ is used. Call can be checked.
    EXPECT_CALL(fooTest, callbackMethod(::testing::_)).Times(1) 
    .WillOnce(testing::InvokeArgument<0>());;
    EXPECT_CALL(testFunc, Call());
    
    testDummy->dummyCallback(testFunc.AsStdFunction());
    
}