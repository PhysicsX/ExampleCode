#include <iostream>
#include <vector>



std::vector<std::pair<int,int>> numberOfMoves(
    std::vector<std::vector<int>> &mat,
    int x,
    int y
)
{
    std::vector<std::pair<int,int>> result;
    
    
    std::vector<int> X = {2, 1, -1, -2, -2, -1,  1,  2};
    std::vector<int> Y = {1, 2,  2,  1, -1, -2, -2, -1};
    
    int numberOfRows = mat.size();
    int numberOfColumns = mat[0].size();
    
    for(int i=0; i<X.size(); i++)
    {
            int p = x + X[i];
            int q = y + Y[i];
            
            if( x <= numberOfRows && y<= numberOfColumns && x>=0 && y>=0)
            {
                    if(mat[p][q] == 0)
                    {
                        
                        result.push_back({p,q});
                    }
            }
        
    
    }
    
    
    
    return result;
}


int main()
{
    
    std::vector<std::vector<int>> mat = {
    {0, 1, 0, 1, 1, 0,},
    {0, 1, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 0,},
    {0, 1, 0, 0, 0, 0,},
    {0, 1, 0, 1, 1, 0,},
    {0, 1, 0, 0, 0, 0,},
    {0, 1, 0, 1, 0, 0,},
    };

    int x = 3;
    int y = 4;
    
    std::vector<std::pair<int,int>> res = numberOfMoves(mat,x,y);
    
    for(auto s : res)
    {
        std::cout<<s.first<<" "<<s.second<<std::endl;
    }
    
    
    return 0;
}