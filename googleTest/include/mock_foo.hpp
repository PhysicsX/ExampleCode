#include "foo_if.hpp"
#include <gmock/gmock.h>
#include <string>

class mockFoo : public fooIf
{
	public:
	MOCK_METHOD(void, fooStr, (std::string& str), (override));
	MOCK_METHOD(void, fooThrow, (), (override));
	MOCK_METHOD(void, callbackMethod, (std::function<void(void)>&),(override));

};
