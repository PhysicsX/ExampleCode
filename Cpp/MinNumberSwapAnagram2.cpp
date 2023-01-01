#include <iostream>
#include <map>
#include <iterator>

// 2186. Minimum Number of Steps to Make Two Strings Anagram II

class Solution {
public:
    int minSteps(std::string s, std::string t) {
        
        std::map<char, int> m;
        for(int i=0; i<s.size(); i++)
        {
            m[s[i]]++;
        }
        int cnt {0};
        for(int i=0; i<t.size(); i++)
        {
            if(s.find(t[i]) != std::string::npos)
            {
                m[t[i]]--;
            }
            else
            {
                cnt++;
            }
        }
    
        for (auto it = m.begin(); it != m.end(); it++)
        {
            cnt = cnt + std::abs(it->second);
        }
        
        return cnt;
    }
};

// faster one
class Solution2
{
public:
    int minSteps(const std::string& s, const std::string& t) {

	// Initialize the counts of each letter to 0
	std::array<int, 26> sCount{};
	std::array<int, 26> tCount{};

	// Count the number of occurrences of each letter in s and t
	for (char c : s) {
		sCount[c - 'a']++;
	}

	for (char c : t) {
    		tCount[c - 'a']++;
  	}

  	int steps = 0;

  	// Count the number of characters in s that are not in t, or the number of extra
  	// occurrences of a character in s
  	for (int i = 0; i < 26; i++) {
    		steps += std::abs(sCount[i] - tCount[i]);
  	}

  	return steps;
    }

};

int main ()
{
    std::string s1 {"leetcode"};
    std::string s2 {"coats"};
    
    std::cout<<Solution{}.minSteps(s1, s2)<<std::endl;
    std::cout<<Solution2{}.minSteps(s1, s2)<<std::endl;
}
