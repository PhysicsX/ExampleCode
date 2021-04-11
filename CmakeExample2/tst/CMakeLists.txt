set(BINARY ${CMAKE_PROJECT_NAME}_tst)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ../src/Formula.h ../src/Example.h ../src/Formula.cpp ../src/Example.cpp *.cpp *.h)

set(SOURCES ${TEST_SOURCES})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC Threads::Threads gtest)