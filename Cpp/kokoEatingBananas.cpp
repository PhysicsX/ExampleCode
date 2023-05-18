#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// leetcode 875. Koko Eating Bananas

// clasic binary search example

// Piles = [3, 6, 7, 11] How many number of bananas should be ate per hour to finish in H hour all piles.
// we can eat 1 banana per hour then total hours will be 27 . 
// we can eat 2 bananas per hour then total hours will be 15 hours.
// maximum number of bananas per hour can be the std::max_element(piles.begin(), piles.end())
// in this case, 11. If 11 bananas is ate per one hour then all piles will finish in 4 hours.
/*
with 1 bananas per hour, all piles will finish in 27 hours
with 2 bananas per hour, all piles will finish in 15 hours
with 3 bananas per hour, all piles will finish in 10 hours
with 4 bananas per hour, all piles will finish in 8 hours
with 5 bananas per hour, all piles will finish in 8 hours
with 6 bananas per hour, all piles will finish in 6 hours
with 7 bananas per hour, all piles will finish in 5 hours
with 8 bananas per hour, all piles will finish in 5 hours
with 9 bananas per hour, all piles will finish in 5 hours
with 10 bananas per hour, all piles will finish in 5 hours
with 11 bananas per hour, all piles will finish in 4 hours

As it is seen, if number of bananas to be ate for per hour is increasing then the
total time to finish all piles is decreasing. This is called monotonic function.
With monotonic function we can use binary search to find desired value.
(brute force will take much time)

simply we have array 1 to 11, it is needed to choose correct number according to the desired hour.
*/

class Solution {

    long long findSuitableHour(const std::vector<int>& piles, int target)
    {
         long long currPile = 0;
         long long hours = 0;
         for(unsigned int i = 0; i < piles.size(); i++)
         {
            const auto& currPile = piles[i];

            if(currPile > target)
            {
                hours += currPile / target;   
                if(currPile % target != 0) hours++;
            }
            else if(currPile <= target)
            {
                hours ++;
            }
         }
         return hours;        
    }

    long long hoursToFinish(std::vector<int>& piles, int bananasForOneHour)
    {
        long long totalHour {0};

        for(const auto& pile : piles)
        {
            totalHour += ceil(pile/(double)bananasForOneHour);
        }
        return totalHour;
    }

public:
    int minEatingSpeed(std::vector<int>& piles, int h) {

        int l=1, r= *max_element(piles.begin(),piles.end());;

        while(l < r)
        {
            // auto mid = l + (r-l)/2;
            auto mid = (l + r) >> 1;

            if(findSuitableHour(piles, mid) <= h) r = mid;
            else l = mid + 1;
        }

        return l;
    }

    int minEatingSpeed_2(std::vector<int>& piles, int hour)
    {
        int max {*std::max_element(piles.begin(), piles.end())};
        int low {1};

        int ans {0};

        while(low <= max)
        {
            int mid = low + (max - low)/2;
            if(hoursToFinish(piles, mid) <= hour)
            {
                ans = mid;
                max = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        return ans;
    }

    int minEatingSpeedBruteForce(const std::vector<int>& piles, int target) {
    
     for(unsigned int j = 1; j <= *max_element(piles.begin(),piles.end()); j++)
     {
         long long hours = 0;

         for(unsigned int i = 0; i < piles.size(); i++)
         {
            const auto& currPile = piles[i];

            if(currPile > j)
            {
                hours += (currPile / j);   
                if((currPile % j) != 0) hours++;
            }
            else if(currPile <= j)
            {
                hours ++;
            }
         }

         if(hours == target)
         {
             return j;
         }

         hours = 0;
    }
     return 0;

    }
};

int main()
{
	std::vector<int> vec {30,11,23,4,20};
	std::cout<<Solution{}.minEatingSpeed(vec, 6)<<std::endl;
	std::cout<<Solution{}.minEatingSpeed_2(vec, 6)<<std::endl;
	
	std::cout<<Solution{}.minEatingSpeedBruteForce(vec, 6)<<std::endl;

        // currPile = currPile - (j*(currPile / j)); ==== currPile = (currPile%j)
	// time exceeded
        std::cout<<Solution{}.minEatingSpeedBruteForce(std::vector<int>{312884470}, 312884469)<<std::endl;
}


