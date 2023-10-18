#include "Data.h"
#include "MockData.h"
#include <memory>

MockData::Ptr global_mock_data_ptr = std::make_shared<MockData>();

#include <iostream>
int Data::call() {
    std::cout<<__LINE__<<std::endl;
    return global_mock_data_ptr->call();
}
