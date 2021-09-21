#include <iostream>
#include <vector>
#include <string>


class Solution
{
    public:
    int longestCommonSubsequence(std::string str1, std::string str2)
    {
        
        std::vector<std::vector<int>> vec(str1.size()+1, std::vector<int>(str2.size()+1,0));
        for(int i = 1; i <= str1.size(); i++)
            for(int j = 1; j <= str2.size(); j++)
                if(str1[i] == str2[j])
                    vec[i][j] = 1 + vec[i-1][j-1];
                else
                    vec[i][j] = std::max(vec[i-1][j], vec[i][j-1]);

        return vec[str1.size()][str2.size()];
    }
};

int main()
{
    std::string str1 {"abcde"};
    std::string str2 {"ace"};

    std::cout<<Solution().longestCommonSubsequence(str1, str2)<<std::endl;
}