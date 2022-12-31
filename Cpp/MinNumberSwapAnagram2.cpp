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
 
int main ()
{
    std::string s1 {"leetcode"};
    std::string s2 {"coats"};
    
    std::cout<<Solution{}.minSteps(s1, s2)<<std::endl;

}
