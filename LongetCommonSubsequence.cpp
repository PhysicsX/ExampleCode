#include <bits/stdc++.h>

using namespace std;

using iter = string::const_iterator;

int MaxChildRanges(iter b1, iter e1, iter b2, iter e2)
{

    if(b1==e1 || b2==e2)
        return 0;

    if(*b1 == *b2)
        return 1 + MaxChildRanges(next(b1), e1, next(b2), e2);

    return max( MaxChildRanges(next(b1), e1, b2, e2),
                MaxChildRanges(b1, e1, next(b2), e2));
}

int commonChild(const string& s1, const string& s2) {

    return MaxChildRanges(s1.begin(), s1.end(), s2.begin(), s2.end());
    
}

int main()
{

    std::string str1 {"SHINCHAN"};
    std::string str2 {"NOHARAAA"};

    int result = commonChild(str1, str2);

    cout << result << "\n";


    return 0;
}
