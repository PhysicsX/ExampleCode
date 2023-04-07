#include <vector>
#include <algorithm>
#include <iostream>

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
        int maxValueWithDoubleLoop(int n, std::vector<std::vector<int>>& rounds)
        {
            std::vector<long long> balances(n+1);
            std::vector<long long> startBalances(n+1);
            std::vector<long long> endBalances(n+1);

            for(auto round : rounds)
            {
                int start = round[0];
                int end = round[1];
                long long amount = round[2];
                startBalances[start] += amount;
                endBalances[end] += amount;
            }

            long long maxBalance = 0;
            for(int i=1; i<=n; i++)
            {
                balances[i] = balances[i-1] + startBalances[i] -endBalances[i-1];
                maxBalance = std::max(maxBalance, balances[i]); 
            }

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
    std::cout << "Maximum investment: " << Solution{}.maxValueWithDoubleLoop(5, rounds) << std::endl;

    return 0;

}