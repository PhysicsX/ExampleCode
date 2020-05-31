/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I

*/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string convert(std::string s, int numRows) {
        if(numRows <= 1) return s;

        std::vector<std::string> vec(numRows); // if array is used memory usage will be low
        
        bool flag = true;
        int y = 0;
        for(int i=0; i<s.size(); i++)
        {
            vec[y] += s[i];
            
            if(y==0) flag = true;
            else if(y==(numRows-1)) flag = false;
            
            if(flag) y++;
            else y--;
        }
        
        std::string ret;
        for(int i=0; i<numRows; i++)
        {
            ret += vec[i];
        }
        
        
        return ret;
    }
};

int main()
{
	Solution s;
	std::string str = "PAYPALISHIRING";
	std::string result = s.convert(str,4);
	std::cout<<result<<'\n';
	return 0;
}


