#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "example.cpp"
#include "MockData.h"

extern std::shared_ptr<MockData> global_mock_data_ptr;

class testFixture : public testing::Test
{
    public:
    testFixture()
    {
    }
    ~testFixture()
    {
        std::move(global_mock_data_ptr).reset(); // delete the global mock
    }
};


TEST_F(testFixture, FooReturnsMockedValue) {

    EXPECT_CALL(*global_mock_data_ptr, call()).WillOnce(::testing::Return(99));

    Example ex; 
    ASSERT_EQ(99, ex.foo());
}
