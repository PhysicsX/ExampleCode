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

        std::vector<int> productExceptSelf3For(std::vector<int>& vec) {
            
            std::vector<int> result;
    
            std::vector<int> left;
            std::vector<int> right;
        
            int leftSum {1};
            for(size_t i{0}; i<vec.size(); i++)
            {
                left.push_back(leftSum);    
                leftSum = leftSum * vec[i];
            }
    
            int rightSum {1};
            for(size_t i{vec.size()}; i>0; i--)
            {
                right.push_back(rightSum);    
                rightSum = rightSum * vec[i-1];
            }

            for(size_t i {0}; i<vec.size(); i++)
            {
                result.push_back(left.at(i) * right.at(vec.size()-1-i));
            }
            return result;
        }
};

int main()
{
    std::vector vec {1,2,3,4};
    
    for(const auto& c : Solution{}.productExceptSelf(vec))
        std::cout<<c<<" ";
        
    std::endl(std::cout);
    
    for(const auto& c : Solution{}.productExceptSelf3For(vec))
        std::cout<<c<<" ";


}