#include "Data.h"
#include <gmock/gmock.h>


class MockData {
public:
    MOCK_METHOD(int, call, ());
    using Ptr = std::shared_ptr<MockData>;
};

// Declare the global pointer to MockData
extern MockData::Ptr global_mock_data_ptr;
