#include <iostream>
#include <algorithm>
#include <vector>

/*
121. Best Time to Buy and Sell Stock
*/

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        
        int result {0};
        int currentMax {0};
        
        for(int i {0}; i < prices.size(); i++)
        {
            int diff = prices[i] - prices[i-1];
            if(diff == 0) continue;
            currentMax = std::max(diff + currentMax, diff);
            result = std::max(result, currentMax);
        }
        return result;
    }
};

int main()
{
    std::vector<int> prices {7,1,5,3,6,4};
    std::cout<<Solution().maxProfit(prices);
    std::cout<<std::endl;
    std::vector<int> prices2 {1,2};
    std::cout<<Solution().maxProfit(prices2);

}