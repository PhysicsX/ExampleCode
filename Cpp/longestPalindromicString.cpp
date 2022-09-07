#include <iostream>
#include <vector>
#include <algorithm>

int lngPalindromicString(std::string str)
{
    size_t size {str.size()};

    std::vector<std::vector<int>> vec(size, std::vector<int>(size,0));

    // fill diagonally with 1 (base case)
    for(size_t i {0}; i<size; i++)
    {
        for(size_t j {0}; j<size; j++)
        {
            if(i == j)
                vec[i][j] = 1;
        }
    }

    // cl is the length of the substring to check
    for(size_t cl {2}; cl<=size; cl++)
    {
        for(size_t i {0}, j {0}; i<(size-cl+1); i++)
        {
            j = i + cl -1; // to choose the element which will be compared

            if(str[i] == str[j])
            {
                vec[i][j] = vec[i+1][j-1] + 2;
            }
            else
            {
                vec[i][j] = std::max(vec[i][j-1], vec[i+1][j]);
            }
        }
    }
    
    return vec[0][size-1];
}


int main()
{
    
    std::string str = "zzabccbassokko";
    
    std::cout<<lngPalindromicString(str);
    
    return 0;
}


/*
    1. Create double vector/table with zeros and set base case filling with 1's diagonally
    2. Check the characters are same or not. First start spatial characters two by two,
    then jump over the characters and continue to check equality.
        for instance: check str[0] == str[1], str[1] == str[2] .....
        then for second iteration
                      check str[0] == str[2], str[1] == str[3] .....
        then for third iteration
                      check str[0] == str[3], str[2] == str[4] .....
        ...
    3. Continue these steps until you reach the right most element of the table which is the result.
    This last element checks the first and last character equality.


    For the given string map should be like:

    1 2 2 2 2 2 4 6 6 6 6 6 6 6 
    0 1 1 1 1 2 4 6 6 6 6 6 6 6 
    0 0 1 1 1 2 4 6 6 6 6 6 6 6 
    0 0 0 1 1 2 4 4 4 4 4 4 4 4 
    0 0 0 0 1 2 2 2 2 2 2 2 2 4 
    0 0 0 0 0 1 1 1 1 2 2 2 2 4 
    0 0 0 0 0 0 1 1 1 2 2 2 2 4 
    0 0 0 0 0 0 0 1 1 2 2 2 2 4 
    0 0 0 0 0 0 0 0 1 2 2 2 2 4 
    0 0 0 0 0 0 0 0 0 1 1 1 2 4 
    0 0 0 0 0 0 0 0 0 0 1 1 2 4 
    0 0 0 0 0 0 0 0 0 0 0 1 2 2 
    0 0 0 0 0 0 0 0 0 0 0 0 1 1 
    0 0 0 0 0 0 0 0 0 0 0 0 0 1 
    
*/