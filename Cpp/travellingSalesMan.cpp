#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

int tsp(int mask, int pos, 
        std::vector<std::vector<int>>& vec, 
        std::vector<std::vector<int>>& dp)
{

    const int size {vec.size()};

    if(mask == ((1<<size)-1))
    {
        return vec[pos][0];
    }

    if(dp[mask][pos] != -1)
    {
        return dp[mask][pos];
    }

    int ans = INT_MAX;

    for(int city=0; city<size; city++)
    {
        if((mask&(1<<city)) == 0)
        {
            int result { vec[pos][city] + tsp(mask|(1<<city), city, vec, dp) };
           ans = std::min(ans, result);
           dp[mask][pos] = ans;
        }
    }
    return dp[mask][pos];
}

int travellingSalesman(std::vector<std::vector<int>>& vec)
{
    std::vector<std::vector<int>> dp(vec.size()*vec.size(),std::vector<int>(vec.size(),-1));
    return tsp(1,0,vec,dp);
}


int main()
{

    std::vector<std::vector<int>> dist{
        {0,20,42,25},
        {20,0,30,34},
        {42,30,0,10},
        {25,34,10,0},
    };

    std::cout<<travellingSalesman(dist)<<std::endl;

}