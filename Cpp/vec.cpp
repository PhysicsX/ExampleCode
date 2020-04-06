/*
 *	Example vector usage
 *	ulasdikme.com
 */
#include <iostream>
#include <vector>
#include <algorithm>

class Example
{
	private:
		int i, y;
	public:
		Example(int i, int y):i(i),y(y){}

		bool operator < (const Example &ex) const
		{
			return i>ex.i;
		}

		//Binary operators can not modify their left operands that is why method should be friend. Note: friend methods are non-member methods even if they implemented in the definition of class.
		friend bool operator > (const Example &lhs, const Example &rhs)
		{
			return lhs.i > rhs.i;
		}

		friend std::ostream &operator <<(std::ostream &out, const Example &ex)
		{
			out<<"i "<<ex.i<<" y "<<ex.y<<std::endl;
			return out;
		}

		static bool comp(const Example &lhs, const Example &rhs)
		{
			return lhs.i > rhs.i;
		}

		int getI()const{ return i; };

		class Comp
		{
			public:
				bool operator ()(const Example &lhs,
						const Example &rhs)
				{
					return lhs.i > rhs.i;
				}
		};

};

bool comparetor(std::pair<int, int> &lhs, std::pair<int, int> &rhs)
{
	return lhs.first > rhs.first;
}

int main()
{
	try
	{
		std::vector<int> vec;
		//to see the effec bad_alloc, command out for(;;)
		//on the same terminal 
		//ulimit -s -V 20000 
		//run the binary
		//after do not forget to run ulimit -S -v unlimited
		//for(;;)
		vec.push_back(1);
	}
	catch(std::bad_alloc e)
	{
		std::cout<<e.what()<<std::endl;
	}

	//std::vector<int> secondVec (10,10);
	//std::cout<<secondVec[10]<<std::endl; //this will violate memory
	//std::cout<<secondVec.at(10)<<std::endl; // this will return out_of_rangee error

	std::vector<int> vec = {1,2,3,4,5,6,7,8,9};
	std::sort(vec.begin(), vec.end(), std::greater<int>());
	
	//iterate through c++11 range based loop
	for(auto s : vec)
		std::cout<<s;


	vec.erase(std::remove_if(vec.begin(), vec.end(),[]
				(int i)
				{
					return i > 5;
				}),
				vec.end());

	std::cout<<"after removing"<<std::endl;

	for(auto s : vec)
		std::cout<<s;

	std::vector<std::pair<int,int>>vec2 =
	{
		{1,9},{2,8},{3,7},{4,6},{5,5},{6,4},{7,3},{8,2},{9,1}
	};

	std::cout<<std::endl;

	//iterate through stl style
	std::vector<std::pair<int, int>>::iterator vecIt;

	for(vecIt = vec2.begin(); vecIt != vec2.end(); vecIt++)
		std::cout<<vecIt->first<<" "<<vecIt->second<<std::endl;


	std::sort(vec2.begin(), vec2.end(), comparetor);
	//std::sort(vec2.begin(), vec2.end(), std::greater<std::pair<int, int>>());
	/*
	 std::sort(vec2.begin(), vec2.end(),[](std::pair<int, int> &lhs,
	 				std::pair<int, int> &rhs)
					{
						return lhs.first > rhs.first;
					}
					);
	 */
	std::cout<<"after sorting"<<std::endl;

	for(auto s : vec2)
		std::cout<<s.first<<" "<<s.second<<std::endl;

	

	typedef std::pair<int, int> ii;
	std::vector<ii> vii;

	
	std::vector<Example> vecExample = 
	{
		{1,9},
		{2,8},
		{3,7},
		{4,6},
		{5,5},
		{6,4},
		{7,3},
		{8,2},
		{9,1}
	
	};

	for(auto s : vecExample)
		std::cout<<s;

	//std::sort(vec.begin(), vec.end());
	//std::sort(vec.begin(), vec.end(), Example::comp); // function object
	//std::sort(vec.begin(), vec.end(), Example::Comp{}); //function object
	std::sort(vecExample.begin(), vecExample.end(), std::greater<Example>());
	
	auto sortEx = [](const Example &lhs, const Example &rhs)
	{
		return lhs.getI() > rhs.getI();
	};

	std::sort(vecExample.begin(), vecExample.end(), sortEx);


	std::sort(vecExample.begin(), vecExample.end(),[](const Example &lhs,
					const Example &rhs)
			{
				return lhs.getI() > rhs.getI();
			});


	std::cout<<"after sorting"<<std::endl;

	for(auto s : vecExample)
		std::cout<<s;



	return 0;

}
