#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

// to order the array/vector in descending order calculate necessary minimum swap number

int numberOfSwap(const std::vector<int>& vec)
{
    unsigned int result{0};
    const size_t size{vec.size()};

    std::vector<std::pair<int, int>> p(size);
    for(size_t i{0}; i<size; i++)
    {
        p[i].first = vec[i];
        p[i].second = i;
    }

    // for descending order
    std::sort(p.begin(), p.end(),
        [](const std::pair<int,int> &p1, const std::pair<int,int> &p2){
            return (p1.first > p2.first);    
        });

    // keep visited nodes in deque
    std::deque<bool> visited(size, false);

    // find cycle in vector/array
    // (edge number of the cycle - 1) is the minimum swap number
    // if there is a back edge that means there is a cycle in the directed graph
    for(size_t i{0}; i<size; i++)
    {
        if(visited[i] || p[i].second == static_cast<int>(i))
            continue;
            
        int edgeNumber{0};
        size_t j {i};
        while(!visited[j])
        {
            visited[j] = true;
            j = p[j].second;
            edgeNumber++;
        }
        
        if(edgeNumber > 0)
            result += (edgeNumber - 1);
    }
    
    return result;
}

int main()
{
    std::vector<int> vec{2, 4, 5, 1, 3};
    std::cout<<numberOfSwap(vec)<<std::endl;
}