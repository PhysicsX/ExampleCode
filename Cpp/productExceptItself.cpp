#include <iostream>
#include <vector>

class Solution
{
    public:
        std::vector<int> productExceptSelf(const std::vector<int>& vec)
        {
            size_t size = vec.size();
            std::vector<int> result(size,1);
            
            int first {1};
            int last {1};
            
            for(size_t i {0}; i<size; i++)
            {
                result[i] *= first;
                first *= vec[i];
                result[size-1-i] *= last;
                last *= vec[size-1-i];
            }
            
            
            return result;
        }
};

int main()
{
    std::vector vec {1,2,3,4};
    
    for(const auto& c : Solution{}.productExceptSelf(vec))
        std::cout<<c<<" ";

}