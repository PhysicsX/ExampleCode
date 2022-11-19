#include <iostream>
#include <algorithm>
#include <vector>

/*
Each day, you can either buy one share of WOT, sell any number of shares
of WOT that you own, or not make any transaction at all. What is the
maximum profit you can obtain with an optimum trading strategy?

- For each share profit is independent. Means that for instance
array = 1,2,100; then for first day buy, second day buy then 
sell the shares in third day -> (100-2) + (100-1) = 197
- Iterate reversely

only difference between maxStock and maxProfit is that for maxStock
profit is added (stock). For maxProfit, it is needed to keep only maximum one
profit.
*/

class Solution
{
    public:
        long maxStock(const std::vector<int>& prices)
        {
            const size_t size {prices.size()};
            long profit {0};
            int peak {0};
           
            for(int i = size-1; i > -1; i--)
            {
                if(prices[i] >= peak)
                    peak = prices[i];
           
                profit += peak - prices[i];
            }
           
            return profit;
        }

        // 121. Best Time to Buy and Sell Stock - leetcode
        long maxProfit(std::vector<int>& prices) {
                    
        const size_t size {prices.size()};
        int profit {0};
        int peak {INT_MIN};
        
        // if iteration is from left to right then instead of peak, min value
        // should be kept (int min{INT_MAX})
        // min = std::min(prices[i],min);
        // profit = std::max(profit, prices[i]-min);
        // because first it is needed to buy the share to sell later
        for(int i = size-1; i>-1; i--)
        {
            peak = std::max(prices[i], peak);   
            profit = std::max(profit, peak - prices[i]);
        }
        
        return profit;
        
    }

};

int main()
{
    std::vector<int> stocks{1,2,100};
    std::cout<<Solution().maxStock(stocks);
    std::endl(std::cout);
    std::cout<<Solution().maxProfit(stocks);

}