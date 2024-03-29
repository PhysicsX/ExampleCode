#ifndef FOO_HPP      
#define FOO_HPP

#include "foo_if.hpp"
#include <string>
#include <functional>

class foo : public fooIf
{
	public:
	int fooInt(std::string& str);
	void fooStr(std::string& str);
	void fooThrow();
	void callbackMethod(std::function<void(void)>& callback);
};

#endif
