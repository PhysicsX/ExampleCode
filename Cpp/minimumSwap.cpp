#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// to order the array/vector in descending order calculate necessary minimum swap number

int numberOfSwap(const std::vector<int>& vec)
{
    int result{0};
    size_t size{vec.size()};
    
    std::vector<std::pair<int, int>> p(size);
    for(size_t i=0; i<size; i++)
    {
        p[i].first = vec[i];
        p[i].second = i;
    }

    std::sort(p.begin(), p.end(),
        [](const std::pair<int,int> &p1, const std::pair<int,int> &p2){
            return (p1.first > p2.first);    
        });

    // keep visited nodes in another vector
    std::vector<bool> vis(size, false);
    
    // find cycle in array
    // (edge number of the cycle - 1) is the minimum operation number
    for(size_t i=0; i<size; i++)
    {
        if(vis[i] || p[i].second == (int)i)
            continue;
            
        int edgeNumber{0};
        int j = i;
        while(!vis[j])
        {
            vis[j] = true;
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