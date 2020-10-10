#include <iostream>
#include <chrono>
#include <future>
#include <atomic>
#include <mutex>

int main()
{
	
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	//int cnt{0};
	std::atomic<unsigned int> cnt{0};
	int iterator{1'000'000};
	std::mutex lockMutex;
	
	
	std::future<void> obj1 = std::async(std::launch::async, [&]()
	{
		//std::lock_guard<std::mutex> guardMutex(lockMutex); //RAII style mechanism
		// lockMutex automatically released when guardMutex is out of scope
		for(int i{0}; i<iterator; i++)
			cnt ++;
	});

	auto obj2 = std::async(std::launch::async, [&]()
	{
		//std::lock_guard<std::mutex> guardMutex(lockMutex);
		for(int i{0}; i<iterator; i++)
			cnt --;
	});

	
	obj1.get();
	obj2.get();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout<<"Time diff "<<std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()<<"[us]"<<std::endl;
	std::cout<<"inc "<<cnt<<std::endl;
	
}