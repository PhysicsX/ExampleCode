#include <iostream>
#include <string>
#include <unordered_map>

bool isAnagram(std::string str1, std::string str2)
{
	if(str1.size() != str2.size())
		return false;

	std::unordered_map<char, int> map;

	for(int i=0; i<str1.size(); i++)
	{
		map[str1[i]]++;
	}


	for(int i=0; i<str2.size(); i++)
	{
	
		if(str2.find(str1[i]) == std::string::npos)
			return false;
		else
		{
		
			map[str2[i]]--;
			if(map[str2[i]] == 0) map.erase(str2[i]);
		}
	}
	// do not print map member here, if it does then size will never not be zero
	return 0 == map.size();

}


int main()
{

	std::string str1 ="ulasdikme";
	std::string str2 ="dikmaulas";

	std::cout<<isAnagram(str1, str2);
	return 0;
}

