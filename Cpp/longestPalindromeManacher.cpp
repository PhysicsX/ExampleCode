#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
	std::string longestPalindrome(std::string s)
	{
		
		if(s.empty()) return "";
		if(s.size() == 1) return s;
		
		std::vector<char> vec2;
		vec2.push_back('$');
		
		for(int i = 1, j = 0; i < (s.size()*2 + 1); i++)
		{
				if(i % 2 == 0)
					vec2.push_back(s[j++]);
				else
					vec2.push_back('#');
		}
		
		vec2.push_back('#');
		vec2.push_back('@');
		
		std::vector<int> P(vec2.size(),0);
		int C = 0;
		int R = 0;
		
		for(int i = 1; i < vec2.size()-1; i++)
		{
			int mirr = 2*C - i;
			if(i < R)
				P[i] = std::min((R-i), P[mirr]);
				
			while( vec2[i + 1 + P[i]] == vec2[i - 1 - P[i]] )
				P[i]++;
				
			if((i + P[i]) > R)
			{
				C = i;
				R = i + P[i];
			}
		}
		
		int max = *std::max_element(P.begin(), P.end());
		std::vector<int>::iterator it = std::find(P.begin(), P.end(), max);
		int index = std::distance(P.begin(), it);
		int init = 0;
		
		if(index % 2 == 0)
			init = std::abs((max / 2)- ( index / 2 - 1));
		else
			init = std::abs((max / 2)- ( index / 2 ));
		
		
		return s.substr(init,max);
	}
};

int main(int argc, char **argv)
{
	const std::string str = "acbbabad";
	
	Solution s;
	std::cout<<s.longestPalindrome(str);
	
	std::cout<<std::endl;
	return 0;
}
