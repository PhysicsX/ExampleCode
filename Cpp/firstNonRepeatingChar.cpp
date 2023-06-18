#include <iostream>
#include <unordered_map>
#include <iostream>

char firstNonRepeatingChar(const std::string& str)
{
    std::unordered_map<char, int> map;

    for(const auto& c : str)
    {
        map[c] ++;
    }

    for(const auto& c : str)
    {
        if(map[c] == 1)
        {
            return c;
        }
    }

    return '\0';
}

int main()
{
    std::string s = "helloFromGithub";
    std::cout<<firstNonRepeatingChar(s);
}