#include <iostream>
#include <vector>
#include <algorithm>
// minimum swap for descending order.

class Solution
{
    public:

        
        int minimumSwapToSort(std::vector<int>& vec)
        {
            int result = 0;
            int size = vec.size();
            
            std::pair<int,int> pos[size];
            
            for(int i = 0; i<size; i++)
            {
                pos[i].first = vec[i];
                pos[i].second = i;
            }
            
            std::sort(pos, pos+size, 
                [](const std::pair<int,int> &p1, const std::pair<int,int> &p2){
                    return (p1.first > p2.first);    
                });
            
            std::vector<int> visited(size, false);
            
            for(int i=0; i<size; i++)
            {
                if(visited[i] || pos[i].second == i)
                    continue;
                
                int cycleSize = 0;
                int j = i;
                while(!visited[j])
                {
                    visited[j] = true;
                    
                    j = pos[j].second;
                    cycleSize++;
                }
                
                if(cycleSize > 0)
                    result += (cycleSize -1);
                    
            }
                                         
            
            return result;
        }
        

};



int main()
{

    std::vector<int> vec {1,5,4,3,2,1};
    
    std::cout<<Solution().minimumSwapToSort(vec);


}
