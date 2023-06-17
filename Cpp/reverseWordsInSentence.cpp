#include <sstream>
#include <deque>
#include <iostream>

std::string reverseWords(std::string str)
{
    std::stringstream ss(str);
    std::string word;

    std::deque<std::string> words;

    while(ss>>word)
    {
        words.push_front(word);
    }

    std::string result;
    while(!words.empty())
    {
        result += words.front() + " ";
        words.pop_front();
    }

    result.pop_back();

    return result;
}

int main()
{
    std::string str = "Electric cars are cool";
    std::cout<<reverseWords(str);
}
