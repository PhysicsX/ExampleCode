#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

/*
1011. Capacity To Ship Packages Within D Days
maximise the minimum || minimise the maximum = BINARY SEARCH ON ANSWER

if the standard output of this function is checked then
it is easy to see that when day in decreasing  capacitiy is increasing 
or vice versa. This is monotonic behaviour capactiy = f(days), to increase the
speed to find the desired capacity, binary search can be used.

day 10 shipCap 1
day 10 shipCap 2
day 9 shipCap 3
day 9 shipCap 4
day 9 shipCap 5
day 8 shipCap 6
day 8 shipCap 7
day 8 shipCap 8
day 7 shipCap 9
day 7 shipCap 10
day 6 shipCap 11
day 6 shipCap 12
day 6 shipCap 13
day 6 shipCap 14
day 5 shipCap 15

*/

class Solution {
public:
// this solution will fail for [1,2,3,1,1]
 int shipWithinDaysBruteForce(std::vector<int>& arr, int totalTrips) {

        for(int shipCap = 1; shipCap<500; shipCap++)
        {
            int currCap = 0;
            int day {1};
            for(const auto weight : arr)
            {
                currCap += weight;
                if(currCap > shipCap)
                {
                    day++;
                    currCap = weight;
                }
            }
            std::cout<<"day "<<day<<" shipCap "<<shipCap<<std::endl;
            if(day <= totalTrips)
            {
                return shipCap;
            }
        }

        return 1;

    }

 int countDays(std::vector<int>& ws, int totCap)
 {
 	int curCap {0};
	int day {1};

	for(const auto w : ws)
	{
		curCap += w;
		if(curCap > totCap) day++, curCap = w;
	}
	return day;
 }

 int shipWithinDays(std::vector<int>& ws, int totalTrips)
 {
    // minimum capacity will be the largest package (for optimize: minimum capacity
    // can not less than r/totalTrips,)
    // for instance: [3, 2, 2, 4, 1, 4]
    // minimum capacity can be 4, but for 2 days 18/2 = 9. 
    // so minimum capacity is 9. No need to check 4 and the numbers 
    // between 4 and 9.
    // for maximum capacity is the sum of all packages.
    
    // maximum capacity is the sum of all packages
 	auto r = std::accumulate(ws.begin(), ws.end(), 0);
	
    // minumum capacity is the largest package
    auto l = std::max(r/totalTrips, *max_element(ws.begin(), ws.end()));
	while(l<r)
	{
		auto m = (l+r)/2;
		if(countDays(ws, m) <= totalTrips) r = m;
		else l = m + 1;
	}
	return l;

    // int res {0};

    // while(l <= r)
    // {
    //     const auto mid = l + (r-l)/2;

    //     if(countDays(ws, mid) <= totalTrips) res=mid, r=mid-1;
    //     else l=mid+1;

    // }

    // return res;

 }
};

int main()
{
	std::vector<int> vec{1,2,3,4,5,6,7,8,9,10};
	int days = 5;
	std::cout<<Solution{}.shipWithinDaysBruteForce(vec,days)<<std::endl;
	std::cout<<Solution{}.shipWithinDays(vec,days)<<std::endl;
}
