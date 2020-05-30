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
        
        for(int i=0; i<logs.size(); i++)
        {
            std::size_t found = logs[i].find_first_of(" ");
            
            size_t count = std::count_if( logs[i].begin()+found, logs[i].end(), 
                                  []( char c ) { return std::isdigit( c ); } );
            
            if(count > 1)
                resDig.push_back(logs[i]);
            else
                 resLet.push_back(logs[i].substr(found+1) + " " + logs[i].substr(0,found));
            
        }
        
        std::sort(resLet.begin(), resLet.end());
        
        for(int i=0; i<resLet.size(); i++)
        {
            std::size_t found = resLet[i].find_last_of(" ");
            resLet[i] = resLet[i].substr(found+1) + " " + resLet[i].substr(0,found);
        }
              
        resLet.insert(resLet.end(),resDig.begin(),resDig.end());
                              
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
