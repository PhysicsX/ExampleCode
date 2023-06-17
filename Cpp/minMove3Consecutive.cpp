#include <iostream>
#include <string>

class Solution
{
    public:
    int minMoves(const std::string& str)
    {
        int res{0};
        size_t size = str.size();

        for(size_t i = 0; i < size;)
        {
            int next = i + 1;

            while( (next < size) && (str[i] == str[next])) {next ++;}
            // next - i is the length of the sequence
            // Each third letter should be changed to remove
            // too long sequenes
            res += (next-i)/3;
            i = next;
        }

        return res;
    }
};

int main()
{
    std::cout<<Solution{}.minMoves("aaabbb");

    
}