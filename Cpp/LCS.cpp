#include <iostream>
#include <string>
#include <vector>

std::string longestCommonSubsequence(const std::string s1, std::string s2)
{
    int n = s1.size();
    int m = s2.size();

    std::vector<std::vector<int>> dp(n+1, std::vector<int>(n+1, 0));

    for(int i=1; i<n; ++i)
    {
        for(int j=1; j<m; ++j)
        {
            if(s1[i-1] == s2[i-2])
            {
                dp[i][j] = dp[i][j] + 1;
            }
            else
            {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    int i = n, j=m;
    std::string lcs;
    /*
    After creating dp table it is possible to find max sub array.
    Start from the right bottom and check the string members if members
    are same then go to previous diagonal position if not then check the numbers
    top and left positions if top is greater than left move --i else --j.
    Because if one positon is greater than other that means there is a match for 
    current character. If there is same char there will be increment.
    */
    while(i>0 && j>0)
    {
        if(s1[i-1] == s2[j-1])
        {
            lcs = s1[i-1] + lcs;
            --i; --j;
        }
        else if(dp[i-1][j] > dp[i][j-1])
        {
            --i;
        }
        else
        {
            --j;
        }
    }
    return lcs;
}

int main()
{
    std::string s1 = "ABCBDAB";
    std::string s2 = "BDCABA";
    std::string lcs = longestCommonSubsequence(s1, s2);
    std::cout << "Longest common subsequence: " << lcs << std::endl; // Output: "BCBA"
    return 0;

}