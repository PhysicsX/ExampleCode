#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <unordered_map>
#include <map>
#include <optional>


    // firstList = {{1, 'a'},{3, 'a'},{4, 'a'}};
    // secondList = {{2, 7.6},{1, 2.8},{4, 5.3}};

    // combine these two lists such as (sorted): {{1, 'a', 2.8}, {2, ,7.6}, {3, 'a', }, {4, 'a', 5.3}}
    // there will not be same key in one list two times, there can be only one or none.

using data = std::tuple<int, std::optional<char>, std::optional<double>>;

std::vector<data> foo(const std::vector<std::pair<int, std::optional<char>>>& vec1,
         const std::vector<std::pair<int, std::optional<double>>>& vec2)
{
    std::unordered_map<int, std::pair<std::optional<char>, std::optional<double>>> map;

    for(const auto& v : vec1)
    {
        if(v.second != std::nullopt)
            map[v.first] = {v.second, std::nullopt};
    }

    for(const auto& v : vec2)
    {
        if(v.second != std::nullopt)
        {
            if(map[v.first].first != std::nullopt)
            {
                map[v.first] = {map[v.first].first, v.second};
            }
            else
            {
                map[v.first] = {std::nullopt, v.second};                
            }
        }
    }

    std::vector<data> result;

    for(const auto& m : map)
    {
        result.push_back({m.first, m.second.first, m.second.second});
    }

    
    std::sort(result.begin(), result.end(), [&](data lhs, data rhs)
    {
        return lhs < rhs;
    });

    return result;
}

int main()
{
    std::vector<std::pair<int, std::optional<char>>> vec1{
        {1, 'a'},
        {2, 'c'},
        {4, 'd'},
        {3, 'b'},
        };

    std::vector<std::pair<int, std::optional<double>>> vec2{
        {6, 1.0},
        {3, 2.34},
        {4, 3.23},
        {1, 1.23},
        };

    auto result = foo(vec1, vec2);

    for(const auto& tuple : result)
    {
        int i = std::get<0>(tuple);
        std::optional<char> c = std::get<1>(tuple);
        std::optional<double> d = std::get<2>(tuple);

        std::cout<<i<<" ";

        if(c)
            std::cout<<*c<<" ";
        else
            std::cout<<"|"<<" ";
        
        if(d)
            std::cout<<*d<<" ";
        else
            std::cout<<"|"<<" ";

        std::endl(std::cout);
    } 

}