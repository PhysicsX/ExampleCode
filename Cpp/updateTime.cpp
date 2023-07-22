#include <vector>
#include <algorithm>
#include <iostream>

class Solution
{
    public:
        int updateTimes(std::vector<int> signalOne,
                        std::vector<int> signalSecond)
        {

            const auto signalOneSize = signalOne.size();
            const auto signalSecondSize = signalSecond.size();
            
            const auto size = std::min(signalOneSize, signalSecondSize);

            unsigned int counter {0};
            int max = 0;
            
            for(int i=0; i<size; ++i)
            {
                int signalOneValue = signalOne[i];
                int signalSecondValue = signalSecond[i];
                
                if(signalOneValue == signalSecondValue)
                {
                    if(signalOneValue > max)
                    {
                        max = signalOneValue;
                        counter ++;
                    }
                }
            }

            return counter;
        }
};

int main() {

    std::vector<int> signalOne      = {1,2,3,3,3,5,4};
    std::vector<int> signalSecond   = {1,2,3,4,3,5,4};
    

    std::cout<<Solution{}.updateTimes(signalOne, signalSecond)<<std::endl;

    std::vector<int> signalOne2      = {1,2,3,4,1};
    std::vector<int> signalSecond2   = {5,4,3,4,1};
    

    std::cout<<Solution{}.updateTimes(signalOne2,
                                      signalSecond2)<<std::endl;

    return 0;
}