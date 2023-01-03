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

class Solution {
public:
bool isAnagram(std::string s, std::string t) {
    // Return false if s and t have different sizes.
    if (s.size() != t.size()) {
        return false;
    }

    // Create an array to store the frequency of each character in s and t.
    std::array<int, 26> sCount{}, tCount{};

    // Iterate through s and t, and increment the corresponding element in sCount and tCount.
    for (int i = 0; i < s.size(); ++i) {
        ++sCount[s[i] - 'a'];
        ++tCount[t[i] - 'a'];
    }

    // Compare sCount and tCount.
    return sCount == tCount;
}
};


int main()
{

	std::string str1 ="ulasdikme";
	std::string str2 ="dikmaulas";

	std::cout<<isAnagram(str1, str2)<<std::endl;
	std::cout<<Solution{}.isAnagram(str1, str2)<<std::endl;
	return 0;
}

