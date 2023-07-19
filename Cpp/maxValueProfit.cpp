#include <vector>
#include <algorithm>
#include <iostream>

// To solve "Prefix sum" can be used.
// So the question is that there is investors these are making investment
// in the predefined range in array. At the end, maximum profit is desired.
/*

    1 2 10 => 1 and 2 are the coordinates of the indices. 10 is the profit

            Total profit
            0  0  0  0  0
    1 2 10  10 10   
    2 4 5   10 15 5  5
    3 5 12  10 10 17 17 12

    At the end max profit is 17.

    In brute force, there can be double for loop to check each input vector and add them to result vector.
    This will lead time complexit for O(n^2)

    To fix this time complexity we can use "Prefix sum"
    Instead of adding each rounds lets add only investment value as a start and end.
    For the first round between 1 and 2 there is 10 profit.
    So, in the investment vector investment[start] += 10; and investment[end-1] -= 10;
    start = 1; end = 2;
    This is because instead of adding each profit in each step, we can track the positons
    and at the end we can add them together (prefix sum) to find the maximum profit/investment

    In simple example lets assume between 2 and 6 we need to add 5
    vector should be [0 5 5 5 5 5 0 0]
    instead of wrtting like this. lets use start and end points
    [0 5 0 0 0 0 0 -5] (vector size should be round+1). 
    then lets use prefix sum to get same result
    vec[1] = 0; vec[2] = vec[1] + vec[2]; vec[3] = vec[0] + vec[1] + vec[2]; .....
    Result = s[0 5 5 5 5 5 5 0].
*/

long maxValue(int n, std::vector<std::vector<int>>& rounds) {
    std::vector<long> investments(n + 1, 0); // Initialize the investment array with n+1 elements, all set to 0

    // Loop through each round and update the investments accordingly
    for (const auto& round : rounds) {
        int start = round[0];
        int end = round[1];
        int contribution = round[2];

        investments[start - 1] += contribution; // Add the contribution to the starting index
        if (end < n) {
            investments[end] -= contribution; // Subtract the contribution from the ending index + 1
        }
    }

    // Calculate the prefix sum of the investments array
    for (int i = 1; i < n; ++i) {
        investments[i] += investments[i - 1];
    }

    // Find the maximum investment value
    long max_investment = *std::max_element(investments.begin(), investments.end() - 1);

    return max_investment;
}

class Solution
{
    public:
        long maxValue(int n, std::vector<std::vector<int>>& rounds) {
            // Initialize vectors to store the balances of each asset
            std::vector<long long> balances(n + 1);
            
            for(auto round : rounds)
            {
                auto start = round[0];
                auto end = round[1];

                auto investment = round[2];

                for(int i=start; i<=end; i++)
                {
                    balances[i-1] += investment;
                }
            }

            auto maxBalance = *std::max_element(balances.begin(), balances.end());

            return maxBalance;
        }
};

int main() {

    //std::vector<std::vector<int>> rounds = {{1, 5, 100}, {2, 4, 200}, {3, 3, 50}};
    std::vector<std::vector<int>> rounds =
    // {{1, 3, 10},
    //  {2, 4, 20},
    //  {1, 4, 5},
    //  {3, 5, 15},
    //  {1, 5, 25}};

    {{1, 3, 5},
     {2, 4, 10},
     {1,2,2},
     {3,4,7}};

    long maxInvestment = maxValue(5, rounds);
    std::cout << "Maximum investment: " << maxInvestment << std::endl;
    std::cout << "Maximum investment: " << Solution{}.maxValue(5, rounds) << std::endl;

    return 0;

}