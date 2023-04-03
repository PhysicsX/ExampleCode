#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;
// g++ cardiSort.cpp -std=c++17
class Solution
{
    public:
        vector<int> cardiSort(vector<int> nums)
        {
            map<int, int> m;
            
            for(int i=0; i<nums.size(); i++)
            {
                m[nums[i]] = countOnes(nums[i]);
            }
            
            multiset<pair<int, int>, ValueComparator> sorted_set(m.begin(), m.end());

            vector<int> result;
            result.reserve(sorted_set.size());

            for(const auto& pair : sorted_set)
            {
                result.push_back(pair.first);
            }

            return result;
        }

    private:
        int countOnes(int n) {
            int count = 0;
            while (n) {
                count += n & 1;
                n >>= 1;
            }
            return count;
        }

        // Comparator for sorting by value
        struct ValueComparator {
            bool operator()(const pair<int, int>& lhs, 
                            const pair<int, int>& rhs) const {
                return lhs.second < rhs.second;
            }
        };
};

class SolutionWithMultiMap
{
    public:
        vector<int> cardiSort(vector<int> nums)
        {
            map<int, int> m;
            
            for(int i=0; i<nums.size(); i++)
            {
                m[nums[i]] = countOnes(nums[i]);
            }
            
            multimap<int, ValueComparator> sorted_set;
            
            for (const auto& kv : m) {
                sorted_set.insert(std::make_pair(kv.second, ValueComparator(kv.first)));
            }

            vector<int> result;

            for(const auto& pair : sorted_set)
            {
                result.push_back(pair.second.value);
            }

            return result;
        }

    private:
        int countOnes(int n) {
            int count = 0;
            while (n) {
                count += n & 1;
                n >>= 1;
            }
            return count;
        }

        // Comparator for sorting by value
        class ValueComparator {
        public:
            int value;
            ValueComparator(int v) : value(v) {}
        };
};

int main() {
    
    vector<int> nums {5, 1, 2, 3, 4, 5};

    for(auto c : Solution{}.cardiSort(nums))
    {
        std::cout<<c<<" ";
    }

    return 0;
}