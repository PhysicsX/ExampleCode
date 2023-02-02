#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
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
	
	std::cout<<Solution{}.minEatingSpeedBruteForce(vec, 6)<<std::endl;

        // currPile = currPile - (j*(currPile / j)); ==== currPile = (currPile%j)
	// time exceeded
        std::cout<<Solution{}.minEatingSpeedBruteForce(std::vector<int>{312884470}, 312884469)<<std::endl;
}


