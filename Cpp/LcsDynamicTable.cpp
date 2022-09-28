#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution
{
    public:
    std::vector<std::vector<int>> vec;
    std::string str1;
    std::string str2;

    Solution(std::string str1_, std::string str2_):
    str1(str1_), str2(str2_)
    {}

    int longestCommonSubsequence()
    {
        const size_t firstStrSize {str1.size()};
        const size_t secondStrSize {str2.size()};

        std::vector<std::vector<int>> vec(firstStrSize+1, 
        std::vector<int>(secondStrSize+1,0));
    
        for(int i = 1; i <= firstStrSize; i++)
            for(int j = 1; j <= secondStrSize; j++)
                if(str1[i-1] == str2[j-1])
                    vec[i][j] = 1 + vec[i-1][j-1];
                else
                    vec[i][j] = std::max(vec[i-1][j], vec[i][j-1]);

        int result = vec[firstStrSize][secondStrSize];
        this->vec = std::move(vec);  

        return result;
    }

    std::string returnLCSstring()
    {
        for(auto v : vec)
        {    for(auto z : v)
            {    
                std::cout<<z<<"   ";
            }
            std::cout<<std::endl;
        }

        int x = str1.size();
        int y = str2.size();
        std::vector<char> result;

        while(y >= 1 && x >= 1)
        {
            if(vec[x][y] == vec[x-1][y])
            {
                x -= 1;
            }
            else if(vec[x][y] == vec[x][y-1])
            {
                y -= 1;
            }
            else
            {            
                y -= 1;
                x -= 1;
                result.push_back(str1[x]); // or str2[y]
            }
        }

        std::reverse(result.begin(), result.end());
    
        return std::string(result.begin(), result.end());
            
    }


};

int main() {

    std::string str1 {"SHINCHAN"};
    std::string str2 {"NOHARAAA"};

    Solution s(str1, str2);
    std::cout<<s.longestCommonSubsequence()<<std::endl;
    std::cout<<s.returnLCSstring()<<std::endl;
}