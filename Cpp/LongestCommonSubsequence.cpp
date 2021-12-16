#include <bits/stdc++.h>
#include <vector>

//A subsequence is a sequence that can be derived from another sequence by deleting some elements without changing the order of the remaining elements. Longest common subsequence (LCS) of 2 sequences is a subsequence, with maximal length, which is common to both the sequences.

using iter = std::string::const_iterator;

int MaxChildRanges(iter b1, iter e1, iter b2, iter e2, 
const std::vector<std::vector<int>>& vec)
{
    auto& mem = vec[e1-b1][e2-b2];
    
    int result;
    if(mem != -1)
        result = mem;
    else if(b1==e1 || b2==e2)
        result = 0;
    else if(*b1 == *b2)
        result = 1 + MaxChildRanges(next(b1), e1, next(b2), e2, vec);
    else
        result = std::max( MaxChildRanges(next(b1), e1, b2, e2, vec),
                    MaxChildRanges(b1, e1, next(b2), e2, vec));

    return result;
}

int commonChild(const std::string& s1, const std::string& s2) 
{
    return MaxChildRanges(s1.begin(), s1.end(), s2.begin(), s2.end(),
    std::vector<std::vector<int>> 
    (s1.size()+1, std::vector<int>(s2.size()+1,-1)));
}

int main()
{
    std::string str1 {"SHINCHAN"};
    std::string str2 {"NOHARAAA"};

    int result = commonChild(str1, str2);

    std::cout << result << "\n";

    return 0;
}