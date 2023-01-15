#include "foo.hpp"

int foo::fooInt(std::string& str)
{
	return str.size();
}

void foo::fooStr(std::string& str)
{
	str = "ExampleStr";
}

void foo::fooThrow()
{
	// throw runtime error
}

void foo::callbackMethod(std::function<void(void)>& callback)
{
	callback();
}