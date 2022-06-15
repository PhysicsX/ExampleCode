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
};

int main()
{
    std::vector<int> prices {7,1,5,3,6,4};
    std::cout<<Solution().maxProfit(prices);
    std::cout<<std::endl; // 5
    std::vector<int> prices2 {1,2};
    std::cout<<Solution().maxProfit(prices2); // 1

}