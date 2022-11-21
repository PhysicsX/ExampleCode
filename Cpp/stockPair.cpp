#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int stockPairs(std::vector<int> stocksProfit, 
                   long target)
    {
        int result {0};
        std::unordered_map<int, int> m;
        for(size_t i{0}; i<stocksProfit.size(); i++)
        {
                m[stocksProfit[i]] ++;
        }

        for(const auto& x : m)
        {
            const long diff {target - x.first};
            if(m.find(diff) != m.end())
            {
                if(m[diff] != 0 && 
                   m[x.first] != 0)
                {
                    result ++;
                    m[diff] --;
                    m[x.first] --;
                }
            }
        }
        return result;
    }
};

int main()
{
    std::vector<int> vec {5, 7, 9, 9, 13, 11, 6, 6, 3, 3};
    int target = 12;

    std::cout<<Solution{}.stockPairs(vec, target);

    return 0;
}