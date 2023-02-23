#include <iostream>
#include <set>
#include <vector>

using namespace std;

// find the element to swap in the first array to make absolute sum diff minimum.
// To point which element is swapped, check closest element to the element with same 
// index in the second array, To do this, copy first array and sort it, use binary
// search to find closest or same number to swap, keep gain for each iteration.

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
                gain = max(gain, original - abs(*prev(it) - nums2[i])); // If you want to see effect of this line, remove it then second test case will give 3157 which should be 3156 :)
         }
     }

     return (res - gain) % 1000000007;

    }
};

int main()
{
 
    std::cout<<Solution{}.minAbsoluteSumDiff({1,10,4,4,2,7}, {9,3,5,1,7,4})<<std::endl;

    std::vector<int> vec1 {53,48,14,71,31,55,6,80,28,19,15,40,7,21,69,15,5,42,86,15,11,54,44,62,9,100,2,26,81,87,87,18,45,29,46,100,20,87,49,86,14,74,74,52,52,60,8,25,21,96,7,90,91,42,32,34,55,20,66,36,64,67,44,51,4,46,25,57,84,23,10,84,99,33,51,28,59,88,50,41,59,69,59,65,78,50,78,50,39,91,44,78,90,83,55,5,74,96,77,46};

    std::vector<int> vec2 {39,49,64,34,80,26,44,3,92,46,27,88,73,55,66,10,4,72,19,37,40,49,40,58,82,32,36,91,62,21,68,65,66,55,44,24,78,56,12,79,38,53,36,90,40,73,92,14,73,89,28,53,52,46,84,47,51,31,53,22,24,14,83,75,97,87,66,42,45,98,29,82,41,36,57,95,100,2,71,34,43,50,66,52,6,43,94,71,93,61,28,84,7,79,23,48,39,27,48,79};
    std::cout<<Solution{}.minAbsoluteSumDiff(vec1, vec2);


    return 0;
}
