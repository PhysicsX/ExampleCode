#include <iostream>
#include <vector>

// 2187. Minimum Time to Complete Trips

class Solution {
public:

    long long minimumTime(std::vector<int>& arr ,  int totalTrips) {
        long long int lowestTime = 1;
        long long int highestTime = 1e14;
        while(lowestTime<highestTime)
        {
            long long int mid = lowestTime + (highestTime-lowestTime)/2;

            if([&]()
            {
                // this lambda will count totalTrips for the given time
            	// a = [1,2,3] , and at time 3 how many trips we can take? 
	        // 3/1 + 3/2 + 3/3 => 3 + 1 + 1 = 5 Trips

                long long int totalTrips = 0;
                for(auto x : arr)
                {
                    // convert it to long long int 
                    long long int val = x;
                    
                    totalTrips += (mid / val);
                }
                return totalTrips;
            }() >= totalTrips)
                highestTime = mid;
            else
                lowestTime = mid+1;
        }
        return lowestTime;
    }
};
 
int main ()
{
    std::vector<int> vec {1,2,3};
    int totalTrips {5};
    
    std::cout<<Solution{}.minimumTime(vec, totalTrips)<<std::endl;
}
