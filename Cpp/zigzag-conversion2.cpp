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
#include <stack>

class Solution {
public:
    std::string convert(std::string s, int numRows) {
  
        if(numRows == 1)
            return s;
        
        std::vector<std::stack<char>> vec(numRows);
        
        int j=0; bool flag = 0;
        for(int i=0; i<s.length(); i++)
        {
            
            vec[j].push(s[i]);

            if(flag == 1) j--;
            if(flag == 0) j++;
            
            if(j == numRows){ flag = 1; j=numRows-2;}
            if(j == -1){flag = 0; j=1;}
        }

      
        std::string result(s.length(),' ');
        j = s.length();
      
        for(int i= vec.size()-1; i>=0; i--)
        {
            while(!vec[i].empty())
            {
                result[j-1] = vec[i].top();
                vec[i].pop();
                j--;
            }
        }
        
        return result;
        
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


