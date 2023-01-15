#ifndef DUMMY_HPP
#define DUMMY_HPP
#include <iostream>
#include <string>
#include "foo_if.hpp"

class dummy
{
	public:
	dummy(fooIf& f):mfoo(f){}
	int dummyInt(std::string& str);
	void dummyStr(std::string& str);
	void dummyThrow();
	void dummyCallback(std::function<void(void)> callback);

	fooIf& mfoo;
};

#endif
