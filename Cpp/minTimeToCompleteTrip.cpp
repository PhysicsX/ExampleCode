#include <iostream>
#include <vector>

// 2187. Minimum Time to Complete Trips

class Solution {

    using lng = long long int;	
public:
	
    long long minimumTime(std::vector<int>& arr ,  int totalTrips) {
        lng lowestTime = 1;
        lng highestTime = 1e14;
        while(lowestTime<highestTime)
        {
            lng mid = lowestTime + (highestTime-lowestTime)/2;

            if([&]()
            {
                // this lambda will count totalTrips for the given time
            	// a = [1,2,3] , and at time 3 how many trips we can take? 
	        // 3/1 + 3/2 + 3/3 => 3 + 1 + 1 = 5 Trips

                lng totalTrips = 0;
                for(const auto& x : arr)
                {
                    // convert it to long long int 
                    lng val = x;
                    
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
