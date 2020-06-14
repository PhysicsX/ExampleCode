cmake_minimum_required(VERSION 3.0)
project(server)


find_package(Boost REQUIRED COMPONENTS system thread)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
  add_executable(server server.cpp)
  target_link_libraries(server ${Boost_LIBRARIES} pthread)
endif()
