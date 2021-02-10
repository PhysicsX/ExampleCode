#include <iostream>
#include <thread>

// g++ nonAutoDuration.cpp -o example -lpthread
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./example
class Example
{
	public:
		int a = 1;
};

void foo()
{
	static Example ex;
	
	ex.a = 1;
	
		std::thread t([&ex]()mutable{
	
			std::cout<<ex.a<<"\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			ex.a = 4;
			std::cout<<ex.a<<"\n";
	
		});
		t.detach();
	//ex.a = 3;
	
}

int main()
{
	

	foo();
/*	
	Example ex;
	ex.a = 2;
	std::thread t([&ex]()mutable{
		std::cout<<ex.a<<std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		ex.a = 4;
		std::cout<<ex.a<<std::endl;
	});
	t.detach();
*/
	std::cout<<"here first\n"<<std::endl;
	while(1);
	//ex.a = 3;
	return 0;
}
