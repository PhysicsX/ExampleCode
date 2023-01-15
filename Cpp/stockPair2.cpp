#include <iostream>
#include <unordered_set>
#include <vector>

// Function to find the number of distinct pairs of stocks that sum to the target profit
class Solution
{
    public:
        int stockPairs(std::vector<int>& profits, int target) {
            // Initialize a hash set to store the profits that have been seen
            std::unordered_set<int> seen;

            // Initialize a counter to keep track of the number of pairs
            int count = 0;

            // Iterate through the array of profits
            for (int profit : profits) {
                // Check if the target profit minus the current profit has been seen before
                if (seen.count(target - profit)) {
                    // If it has, increment the counter
                    count++;
                }
                // Add the current profit to the hash set
                seen.insert(profit);
                }

            // Return the number of pairs found
            return count;
        }
};

int main() {
    // Define the array of profits and the target profit
    std::vector<int> profits = {5, 7, 9, 9, 13, 11, 6, 6, 3, 3};
    int target = 12;

    std::cout<<Solution{}.stockPairs(profits, target);
}