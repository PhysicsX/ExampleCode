#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>

/*
 * 
 * Given string find firt non repeating unique character if there is none return -1
 * 
 * leetcode returns 0
 * loveleetcode returns 2
 * 
 * */


using namespace std;

class Solution
{
     
     public:
        int firstUniqueCharacterInString(string &str)
        {
            
            std::unordered_map<char, int> map;
            int ans = INT_MAX;
            
            for(int i=0; i<str.size(); i++)
            {
                    if(map.find(str[i]) == map.end())
                    {
                        map[str[i]] = i;
                    }
                    else
                    {
                        map[str[i]] = INT_MAX;
                    }
            }
            
            for(auto s : map)
                ans = min(s.second, ans);
            
    
            return (ans == INT_MAX) ? -1 : ans;
                
        }
};



int main()
{
    
        string str = "loveleetcode";
        
        Solution s;
        std::cout<<s.firstUniqueCharacterInString(str)<<std::endl;
        
        return 0;
}