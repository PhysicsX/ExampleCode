#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

/*
121. Best Time to Buy and Sell Stock

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

*/

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        
        int maxPro{0}, mn{INT_MAX};
        
        for(size_t i{0};i<prices.size();i++)
        { 
            mn=std::min(mn,prices[i]);
            maxPro=std::max(maxPro,prices[i]-mn);
        }
        return maxPro;
    }

    int maxProfit_v2(std::vector<int>& prices)
    {
        int currentMax {0}, max{0};

        for(int i=0; i<prices.size()-1; ++i)
        {
            int diff = prices[i+1] - prices[i];
            if(diff == 0) continue;
            // if previous profit is less than the current one (negative profit = loss)
            // then it should be discarded
            // that is why maximum of (diff+currentMax) and diff
            // is checked here
            currentMax = std::max(diff+currentMax, diff);
            max = std::max(currentMax, max);
        }

        return max;
    }
};

int main()
{
    std::vector<int> prices {7,1,5,3,6,4};
    std::cout<<Solution().maxProfit(prices);
    std::cout<<std::endl; // 5
    std::vector<int> prices2 {1,2};
    std::cout<<Solution().maxProfit(prices2); // 1
    std::cout<<std::endl;

    std::cout<<Solution().maxProfit_v2(prices); // 5


}