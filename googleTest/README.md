## Gtest example with gmock

Install googletest and compile
```bash
$ git clone https://github.com/google/googletest.git -b release-1.12.0
$ cd googletest
$ mkdir build
$ cd build
$ cmake .. -DBUILD_GMOCK=OFF
$ make
```

Please check the current release version and update the git clone command accordingly.

After this, your related static binaries will be in the googletest/build/lib/ location.  

To test it, let's write a simple hello world gtest application. (you can find it as an example.cpp in the repo)
```bash
# cd ..
# mkdir googleTest
# cd googleTest
```
content of example.cpp
```bash
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

TEST(TestName, test1)
{
	ASSERT_EQ(1, 1);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
```
Here, one main method and one test method have the name TestName.test1. To compile it, you can use simply:

```bash
<<<<<<< HEAD
$ g++ example.cpp ../googletest/build/lib/libgtest.a ../googletest/build/lib/libgtest_main.a -lpthread -I ../googletest/googletest/include/
=======
g++ example.cpp ../googletest/build/lib/libgtest.a googletest/build/lib/libgtest_main.a -lpthread -I googletest/googletest/include/
>>>>>>> e73449202a0b37e0c835d83d7739327bb60c2972
```

After this, it will give you a.out when you run it.

```bash
jnano@jnano:~$ ./a.out 
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from TestName
[ RUN      ] TestName.test1
[       OK ] TestName.test1 (0 ms)
[----------] 1 test from TestName (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.
```

If you want to test method of a class, you need to create an object inside these tests or need to create one global object.


```bash
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

class example
{
	public:
		int foo()
		{
			return 1;
		}
		
};

TEST(TestName, test1)
{
	example ex;
	ASSERT_EQ(1,ex.foo());
}

TEST(TestName, test2)
{
	example ex;
	ASSERT_NE(0,ex.foo());
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


```

Therefore, these are not cool solutions, so we need a design or approach that we can keep all objects which are under test under single class.
We can do this with test fixtures:


```bash
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

class example
{
	public:
		int foo()
		{
			return 1;
		}
		
};

class exampleFixture : public testing::Test 
{
	public:
	exampleFixture(){
		testExPtr = new example();
	}
	~exampleFixture()
	{
		delete testExPtr;
	}

	void SetUp(){}
	void TearDown(){}
	
	example* testExPtr;
};

TEST_F(exampleFixture, test1)
{
	ASSERT_EQ(1,testExPtr->foo());
}

TEST_F(exampleFixture, test2)
{
	ASSERT_NE(0,testExPtr->foo());
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
```
As you see, after TEST macro there is _F. And each test case starts with name of the class which encapsulates object under test.


But we do not use the command line to compile our projects. Then it is a good idea to use CMake to compile all.
Create a file named CMakeLists.txt

Then copy below content to file.
```bash
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

project(ExampleGtest LANGUAGES CXX)

include_directories(../googletest/googletest/include)
add_executable(${PROJECT_NAME} example.cpp)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/../googletest/build/lib/libgtest.a ${CMAKE_SOURCE_DIR}/../googletest/build/lib/libgtest_main.a)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)
```
What do we apply here, simply link the static binaries and include headers with cmake.
But this is a best practice ? 
Nope.
Then what ?

If you check here https://cmake.org/cmake/help/latest/module/FetchContent.html, you can see that we can fetch the content from the repository directly. No need to build.
Like :

```bash
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

project(ExampleGtest LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        bf66935e07825318ae519675d73d0f3e313b3ec6 
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} example.cpp)

target_link_libraries(${PROJECT_NAME} gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

#include headers
include_directories(include)
```

This will compile and fetch the gtest accordingly, so there is no need to compile by hand. And no need to care about the static files. You can give the desired commit number. Be careful about the CMake version; it cannot be available for old versions.
And there is one more benefit here. gtest_discover_tests make us to remove main() function in the example.cpp. That means we do not have to init google test and run it. Just simply define the tests.

## Gmock example

So what is gmock? When you have dependencies for your object during unit testing, these dependencies should be mocked. When you mocked them, your object does not call the real methods of dependencies but mocked methods.

It will be good to have to use interfaces in your design. (the interface is a good thing )

For instance, in this example, you can see that the foo class is mocked; if you check under the include directory, there is a mock_foo.hpp file. ( keeping this in include with others is not a good idea, of course).

```bash
#include "foo_if.hpp"
#include <gmock/gmock.h>
#include <string>

class mockFoo : public fooIf
{
	public:
	MOCK_METHOD(void, fooStr, (std::string& str), (override));
	MOCK_METHOD(void, fooThrow, (), (override));
	MOCK_METHOD(void, callbackMethod, (std::function<void(void)>),(override));

};
```

As you see, it implements the fooIf interface. The way of implementation is different from a syntax perspective. You need to use MOCK_METHOD gtest macro and first define the return of the function, then name the arguments finally.

To inject this, you will use the constructor of your object.

```bash
testDummy = std::make_unique<dummy>(fooMock);
```
Because we can pass it, why ? we use same interface, so we are able to see here that one of the advantage of using interfaces.

Then in the test fixture, you can use it like :
```bash
EXPECT_CALL(fooMock, fooStr(::testing::_)).WillOnce(::testing::SetArgReferee<0>(returnStr));
```
What does it mean ? Simply fooStr method of the mock must be called and return the string from argument for this test, otherwise gtest will fail.

If you want you can check this diagram to understand the relationship better for mock and test classess. ( design is for this simple example. Relationship can be different according to you requirements. )

![Class Diagram](https://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/PhysicsX/ExampleCode/master/googleTest/test.puml)

So as you see test class (text fixture) has composition dependency to dummy class which will be tested, and to mockFoo class, not foo class. In this way, during a test, real methods of the foo object will not be called. This is because of the mock mechanism.
 
So the question is that why we do not use foo itself instead of mockFoo. Because we want to test only dummy class not foo or others. This is the point of unit test. Foo object can have some dependecny which can not be relevant for dummy object test. We need to remove them from the test but at the same time we should not change anything in the dummy implementation so we should mock the dependecies of the dummy object which we want to test.

## Line Coverage
If you check the cmakelists.txt in the repository, then you will see extra commands like gcov and lcov.
These are used to calculate line coverage. What is linecoverage? Simply it will give you the numbers of the lines and coverage that you test in your code base.
To install it on Ubuntu
```bash
$ sudo apt-get -y install lcov
```

```bash
# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p gcoverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND ${GCOV_PATH} -b ${CMAKE_SOURCE_DIR}/src/*.cpp -o ${OBJECT_DIR} 
    COMMAND echo "-- Source diretorie: ${CMAKE_SOURCE_DIR}/src/"
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/gcoverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gcoverage
    )

add_dependencies(gcov ${PROJECT_NAME})

add_custom_target(lcov
    COMMAND mkdir -p lcoverage
    )

add_custom_command(TARGET lcov
    COMMAND echo "=================== LCOV ===================="
    COMMAND echo "-- Passing lcov tool under code coverage"
    COMMAND lcov --capture --directory ${OBJECT_DIR} --output-file lcoverage/main_coverage.info -b .
    COMMAND echo "-- Remove undesired files from main_coverage"
    COMMAND lcov --remove lcoverage/main_coverage.info '*/usr/include/*' '*/gtest/*' -o lcoverage/filtered_coverage.info
    COMMAND echo "-- Generating HTML output files"
    COMMAND genhtml lcoverage/filtered_coverage.info --output-directory lcoverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES gcoverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files. ${CMAKE_MAKE_PROGRAM} is /usr/bin/make
add_custom_target(refresh
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm CMakeCache.txt
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
```

I created here three different targets in the cmakelists.txt. What is a target? When you run the "make" command, you can "make -targetName-". For instance, one target is "gcov". After compilation, when you run "make gcov" you will see that all files are processed in your application. This will produce .gcov files where you can find line coverage information. But it is not human-readable, and there are other files that we do not need. It will produce all linked binaries, for instance, gtest and included libraries. We should remove them.

We can remove them during lcov process. Lcov is a tool to create html readable format for line coverage.
then run "make lcov"

```bash
Generating output.
Processing file src/foo.cpp
Processing file src/example.cpp
Processing file src/dummy.cpp
Writing directory view page.
Overall coverage rate:
  lines......: 52.6% (10 of 19 lines)
  functions..: 70.0% (7 of 10 functions)
Built target lcov
```

This will produce lcoverage directory go there, then you may be able to see index.html file. Open it using one of your favorite web browser. You should see sth like this:

![alt text](linecoverage.png?raw=true)

You can check the line coverage visually file by file.
Btw, I added all the stuff in one CMakeLists.txt file, I think it is not best practice, it is a good idea to split it :)

## Gmock example

So what is gmock ? When you have dependecies for your object, during the unit testing these dependencies should be mocked. When you mocked them, your object does not call the real methods of dependencies but mocked methods. 
It will be good to have to use interfaces in your design. ( interface is good thing )

For instance in this example you can see that foo class is mocked, if you check under include directory, there is a mock_foo.hpp file. ( keeping this in include with others is not a good idea ofcourse).

```bash
#include "foo_if.hpp"
#include <gmock/gmock.h>
#include <string>

class mockFoo : public fooIf
{
	public:
	MOCK_METHOD(int, fooInt, (std::string& str), (override));
	MOCK_METHOD(void, fooStr, (std::string& str), (override));
	MOCK_METHOD(void, fooThrow, (), (override));
	MOCK_METHOD(void, callbackMethod, (std::function<void(void)>),(override));

};
```

As you see, it implements the fooIf interface. The way of implementaion is different from syntax perspective. You need to use MOCK_METHOD gtest macro and first define return of function then name finally the arguments.
To inject this, you will use constructor of your object.

```bash
testDummy = std::make_unique<dummy>(fooMock);
```
Because we can pass it, why ? we use same interface, so we are able to see here that one of the advantage of using interfaces.

Then in the test fixture, you can use it like :
```bash
EXPECT_CALL(fooMock, fooStr(::testing::_)).WillOnce(::testing::SetArgReferee<0>(returnStr));
```
What does it mean ? Simply fooStr method of the mock, must be called and return the string from argument for this test, otherwise gtest will fail.

Not for all cases it is necessary to inherit the interface. According to situation, it is possible to use mock class without inheritance. This usage is called standalone mocking.

If you want you can check this diagram to understand the relationship better for mock and test classess. ( design is for this simple example. Relationship can be different according to you requirements. )

![Class Diagram](https://www.plantuml.com/plantuml/proxy?src=https://raw.githubusercontent.com/PhysicsX/ExampleCode/master/googleTest/test.puml)

 so as you see test class (text fixture) has composition dependecy to dummy class which will be tested, and to mockFoo class not foo class. In this way, during test, real methods of the foo object will not be called. This is because if the mock mechanism.
 
 So the question is that why we do not use foo itself instead of mockFoo. Because we want to test only dummy class not foo or others. This is the point of unit test. Foo object can have some dependecny which can not be relevant for dummy object test. We need to remove them from the test but at the same time we should not change anything in the dummy implementation so we should mock the dependecies of the dummy object which we want to test.

