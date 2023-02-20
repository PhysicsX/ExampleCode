#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    int minAbsoluteSumDiff(const vector<int>& nums1, const vector<int>& nums2) {

     long res = 0, gain = 0;
     set<int> s(nums1.begin(), nums1.end());
     for(int i=0; i<nums1.size(); ++i)
     {
         long original = abs(nums1[i] - nums2[i]);
         res += original;
         if(gain < original)
         {
             auto it = s.lower_bound(nums2[i]);
             if(it != s.end())
                gain = max(gain, original - abs(*it - nums2[i]));
            if(it != s.begin())
                gain = max(gain, original - abs(*prev(it) - nums2[i]));
         }
     }

     return (res - gain) % 1000000007;

    }
};

int main()
{
 
    std::cout<<Solution{}.minAbsoluteSumDiff({1,10,4,4,2,7}, {9,3,5,1,7,4});
    return 0;
}
