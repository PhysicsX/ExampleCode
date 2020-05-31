/*
	Recorder Data in Log Files
	You have an array of logs. Each log is a space deliminated string of words.
	For each log, the fisrt word in each log is an alphanumeric identifier. Then, either;
		- Each word after the identifier will consist only of lowercase letters, or;
		- Each word after the identifier will consist only of digits.
	We will call these two varieties of logs letter-logs and digit-logs. It is guaranteed that each log has at least one word after its identifier.
	Recorder the logs so that all of the letter logs come before any digt-log. The letter-logs are orderedd lexicographically ignoring identifier, with the 
	identifier used in case of ties. The digit-logs should be put in their original order.
	Return the final order of the logs.
	Example 
	Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
	output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
*/
//Runtime: 12 ms, faster than 96.91% of C++ online submissions for Reorder Data in Log Files.
//Memory Usage: 11.2 MB, less than 100.00% of C++ online submissions for Reorder Data in Log Files.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        

        vector<string> resLet;
        vector<string> resDig;
        
        for(std::string &s : logs)
        {
            if(std::string::npos != ((s.substr(s.find_first_of(" ")+1)).find_first_of("0123456789")))
                resDig.push_back(s);
            else
                resLet.push_back(s.substr(s.find_first_of(" ")+1) + " " + s.substr(0,s.find_first_of(" ")));
            
        }
        
        std::sort(resLet.begin(), resLet.end());
        
        for(std::string &s : resLet) 
            s = s.substr(s.find_last_of(" ")+1) + " " + s.substr(0,s.find_last_of(" "));

        for(std::string &s : resDig) resLet.push_back(s);
                              
        return resLet;
    }
};

int main()
{
	vector<string> log = {"dig1 8 1 5 1", "let1 art can", "dig2 3 6","let2 own kit dig","let3 art zero"};


	Solution s;

	vector<string> res = s.reorderLogFiles(log);

	for( auto s : res )
	cout<<s<<endl;

	return 1;
}
