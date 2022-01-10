#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

//A subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements. Longest common subsequence (LCS) of 2 sequences is a subsequence, with maximal length, which is common to both the sequences.

using iter = std::string::const_iterator;
using doubleMap = std::vector<std::vector<int>>;

int maxChildRanges(iter b1, iter e1, iter b2, iter e2, doubleMap& map)
{
    auto& mem {map[e1-b1][e2-b2]};
    int result {0};

    if(mem != -1)
        result = mem;
    else if(b1==e1 || b2==e2)
        mem = 0;
    else if(*b1 == *b2)
        result = mem = 1 + maxChildRanges(next(b1), e1, next(b2), e2, map);
    else
        result = mem = std::max(maxChildRanges(next(b1), e1, b2, e2, map),
                        maxChildRanges(b1, e1, next(b2), e2, map));

    return result;
}

int commonChild(const std::string str1, const std::string str2)
{
    doubleMap map{str1.size()+1,std::vector<int>(str2.size()+1, -1)};
    return maxChildRanges(str1.begin(), str1.end(), str2.begin(), str2.end(), map);
}

int main()
{
    std::string str1{"SHINCHAN"};
    std::string str2{"NOHARAAA"};
    
    std::cout<<commonChild(str1, str2)<<std::endl;
    
    return 0;
}