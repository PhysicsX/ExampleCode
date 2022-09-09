#include <iostream>
#include <string>

class Solution
{
public:
    std::string longestPalindrome(const std::string& s)
    {
        size_t size {s.size()};
        
        unsigned int max_length {0};
        unsigned int min_start {0};

        for(unsigned int i{0}; i < size;)
        {
            if((size-i) <= max_length/2) break;
            unsigned int k {i}, j {i};

            while( k<size-1 && s[k+1] == s[k]) k++; // skip duplicate elements

            i = k + 1;
            while( k<size-1 && j > 0 && (s[k+1] == s[j-1])) // expand
            {
                ++k;
                --j;
            }

            unsigned int new_length {k-j+1};
            if(new_length > max_length){ max_length = new_length; min_start=j;}
        }

        return size ? size==1 ? s : s.substr(min_start,max_length) : "";
    }
};

int main()
{
	const std::string str = "asddabbasswe";
	
	std::cout<<Solution{}.longestPalindrome(str);

    return 0;
}