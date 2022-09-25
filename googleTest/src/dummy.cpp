#include "dummy.hpp"

int dummy::dummyInt(std::string& str)
{
	return mfoo.fooInt(str);
}

void dummy::dummyStr(std::string& str)
{
	mfoo.fooStr(str);
	//str = "ExampleStr";
}

void dummy::dummyThrow()
{
	mfoo.fooThrow();
}

void dummy::dummyCallback(std::function<void(void)> callback){
	mfoo.callbackMethod(callback);
}

