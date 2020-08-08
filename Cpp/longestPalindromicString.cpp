#include <iostream>
#include <vector>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int lngPalindromicString(std::string str)
{
    int size = str.size();
    
    std::vector<int> v(size);
    std::vector<std::vector<int>> vec(size,v);
    
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
                if(i==j)
                    vec[i][j] = 1;
                else
                    vec[i][j] = 0;
        }
    }

    // cl is the length of the current string to check
    for(int cl = 2; cl<=size; cl++)
    {
        for(int i=0, j=0; i < (size - cl + 1); i++)
        {
            j = i + cl - 1;
            
            if(str[i] == str[j])
                vec[i][j] = vec[i+1][j-1] + 2;
            else
                vec[i][j] = max(vec[i][j-1], vec[i+1][j]);
        }
    }



    return vec[0][size-1];
}

int main()
{
    
    std::string str = "abccba";
    
    std::cout<<lngPalindromicString(str);
    
    
    return 0;
}