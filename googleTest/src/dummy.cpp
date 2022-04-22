#include "dummy.hpp"

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

