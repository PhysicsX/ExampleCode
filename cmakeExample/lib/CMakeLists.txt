add_library(lib SHARED src/lib.cpp)

message("${CMAKE_CURRENT_SOURCE_DIR} is the current source")
set(CMAKE_SHARED_LIBRARY_PREFIX "s") # change prefix

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)