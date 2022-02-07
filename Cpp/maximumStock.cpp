#include <iostream>
#include <algorithm>
#include <vector>

/*
Each day, you can either buy one share of WOT, sell any number of shares
of WOT that you own, or not make any transaction at all. What is the
maximum profit you can obtain with an optimum trading strategy?
*/

class Solution
{
    public:
        long maxStock(const std::vector<int>& prices)
        {
            const int size = prices.size();
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

};

int main()
{
    std::vector<int> stocks{1,2,100};
    std::cout<<Solution().maxStock(stocks);
}