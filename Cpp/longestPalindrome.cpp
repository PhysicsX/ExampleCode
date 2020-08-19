#include <stdio.h>
#include <iostream>

using namespace std;

class Solution
{
public:
	string longestPalindrome(string s)
	{
		
		if(s.empty()) return "";
		if(s.size() == 1) return s;
		int min_start = 0, max_len = 1;
		for(int i = 0; i < s.size();)
		{
				if(s.size() - i <= max_len / 2) break;
				int j = i, k = i;
				while(k < s.size()-1 && s[k + 1] == s[k]) ++k; // skip duplicate characters
				i = k + 1;
				while(k < s.size()-1 && j > 0 && s[k + 1] == s[j - 1])
				{
					++k; 
					--j;
				} // expand
				int new_len = k - j + 1;
				if(new_len > max_len){min_start = j; max_len = new_len;}
		}
		return s.substr(min_start, max_len);
	}
};

int main(int argc, char **argv)
{
	const string str = "acbbabad";
	
	Solution s;
	std::cout<<s.longestPalindrome(str);
	
	cout<<endl;
	return 0;
}
