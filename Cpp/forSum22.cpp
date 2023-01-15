#include <iostream>
#include <bitset>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
            bitset<4901> p(1);
            
            // this will create bitset which has all possibilities
            // of the additions from each row of the elements.
            // first row is shifted to left then in the second 
            // iteration this bitset is used as default to be shifted
            // to the left according the next vector content.
            // at the end, each bitset position shows the addition 
            // of all possibilities.
            for (auto& r : mat) {
                bitset<4901> tmp;
                for (int i : r) {
                    tmp = tmp | (p << i);
                }
                swap(p, tmp);
            }

            int result {INT_MAX};
            for (int i {0}; i < 4901; ++i) {
                if (p[i]) {
                    int distance = abs(i - target);
                    result = min(result, distance);
                }
            }
            
            return result;
    }
};

int main()
{
    vector<vector<int>> vec{ {1,2,3},{4,5,6},{7,8,9} };

    std::cout<<Solution{}.minimizeTheDifference(vec, 12);

    return 0;
}