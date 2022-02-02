#include <iostream>
#include <string>
#include <vector>

// find the number of months for k number which is used to count 
// the number of months that are increased consecutively

class Solution
{
    public:
        int countProfitableMonths(std::vector<int>& vec, int k)
        {
            int result {0};
            size_t size {vec.size()};
        
            int cnt {0};
            for(size_t i=1; i<size; i++)
            {
                int diff {vec[i] - vec[i-1]};
                
                if( diff > 0)
                {
                    cnt ++;
                    unsigned int l = i+1;
                    if( l >= size)
                    {
                        if(k == 2)
                        {
                            result++;
                            break;
                        }
                    }
                    while(1)
                    {
                        int tempDiff {vec[l] - vec[l-1]};
                        if( tempDiff > 0)
                        {
                            l++;
                            cnt++; 
                            
                            if(k == 2)
                            {
                                if(cnt == k)
                                {
                                    result ++;
                                    cnt = 0;
                                    break;
                                }
                            }
                            else if( k > 2)
                            {
                                if(cnt == k-1)
                                {
                                    result ++;
                                    cnt = 0;
                                    break;
                                }  
                            }
                        }
                        else
                        {
                            cnt = 0;
                            break;    
                        }
                    }
                }
                else
                    cnt = 0;
            }
            return result;
        }
};

int main()
{
    std::vector<int> vec {5, 3, 5, 7, 8, 9, 10, 11};
    //std::vector<int> vec {5, 3, 5, 7, 8};
    //std::vector<int> vec { 1, 5, 2, 3, 7, 6, 4, 5 };
    std::cout<<Solution().countProfitableMonths(vec, 3);
}
