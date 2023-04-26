#include <iostream>
#include <stack>
#include <deque>
#include <string>

// super reduced string hackerRank
// Reduce a string of lowercase characters in
// range ascii[‘a’..’z’]by doing a series of operations. In each operation, select a pair of adjacent letters that match, and delete them.
// aab shortens to b in one operation: remove the adjacent a characters.
// abccbd => ad

using namespace std;

// custom char inherited stack to use protected member c
class customCharStack : public std::stack<char, std::deque<char>>
{
    public:
        const std::deque<char>& get_underlying_container() const 
        {
            return this->c; // c is protected in std::stack
        }
};

string superReducedString(string str) {

    customCharStack stackStr;

    for(const auto s : str)
    {
        if(!stackStr.empty() && s == stackStr.top())
            stackStr.pop();
        else
            stackStr.push(s);
    }

    const std::deque<char>& underlying_container = stackStr.get_underlying_container();

    std::string result;

    for(auto it = underlying_container.rbegin(); it != underlying_container.rend(); ++it)
    {
        result += *it;
    }

    if(result.empty())
        return "Empty String";

    return result;
}



int main() {

    std::string str("acdqglrfkqyuqfjkxyqvnrtysfrzrmzlygfveulqfpdbhlqdqrrqdqlhbdpfqluevfgylzmrzrfsytrnvqyxkjfquyqkfrlacdqj");

    const auto result = superReducedString(str);

    std::cout<<result<<std::endl;

    if(result != "acdqgacdqj")
    {
        std::cout<<"Output correct !";
    }
    else
    {
        std::cout<<"Output is not correct";
    }

    return 0;
}
