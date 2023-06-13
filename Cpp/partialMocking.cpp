#include <gtest/gtest.h>
#include <gmock/gmock.h>
// https://godbolt.org/z/jqEhvo13Y

class Concrete {
public:
    int NonMockedMethod() {
        return 42;
    }

    virtual int MockedMethod() {
        return 43;
    }
};

class MockConcrete : public Concrete {
public:
    MOCK_METHOD(int, MockedMethod, (), (override));

    MockConcrete() {
        // Call the real implementation by default
        ON_CALL(*this, MockedMethod())
            .WillByDefault([this]() { return Concrete::MockedMethod(); });
    }
};

TEST(MockConcreteTest, CanMockConcrete) {
    MockConcrete obj;
    
    // When we call NonMockedMethod, we call the real implementation
    EXPECT_EQ(42, obj.NonMockedMethod());
    
    EXPECT_EQ(43, obj.MockedMethod());

    // We can still override MockedMethod to return a different value
    EXPECT_CALL(obj, MockedMethod()).WillOnce(::testing::Return(44));
    EXPECT_EQ(44, obj.MockedMethod());
}