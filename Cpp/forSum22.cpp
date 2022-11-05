#include <iostream>
#include <bitset>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
            bitset<4901> p(1);
            
            for (vector<int>& r : mat) {
                
                bitset<4901> tmp;
                for (int i : r) {
                    std::cout<<i<<std::endl;

                    tmp = tmp | (p << i);
                    std::cout<<tmp.to_string()<<" ";
                    std::cout<<std::endl;

                }
                std::cout<<std::endl;
                swap(p, tmp);
            }

            int result = INT_MAX;
            for (int i = 0; i < 4901; ++i) {
                if (p[i]) {
                    std::cout<<i<<" "<<std::endl;
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