#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
        int numIslands(vector<vector<char>> &grid)
        {
            int result = 0; // number of islands
            if(grid.size() == 0)
                return result;
                
            int numberOfRows = grid.size();
            int numberOfColumns = grid[0].size();
 
            // it is like possible moves of knight -> https://www.geeksforgeeks.org/possible-moves-knight/
            vector<pair<int,int>> neighboorCorr = {{0,1},{1,0},{0,-1},{-1,0}};
            
            for(int i=0; i<numberOfRows; i++)
            {
                    for(int j=0; j<numberOfColumns; j++)
                    {
                            if(grid[i][j] == '1')
                            {
                                
                                result++;
                                queue<pair<int,int>> que;
                                que.push({i,j});
                                grid[i][j] = '0';
                                
                                while(!que.empty())
                                {
                                        auto p = que.front();
                                        que.pop();
                                        
                                        for(unsigned int k=0; k<neighboorCorr.size(); k++)
                                        {
                                            int x = p.first + neighboorCorr[k].first;
                                            int y = p.second + neighboorCorr[k].second;
                                            
                                            if( x>=0 && x<numberOfRows && y>=0 && y<numberOfColumns)
                                            {
                                                    if(grid[x][y] == '1')
                                                    {
                                                            grid[x][y] = '0';
                                                            que.push({x,y});
                                                    }
                                            }
                                        }
                                }
                                
                                
                            }
                    }
            }
            
            return result;
        }
};


int main(int argc, char **argv)
{

    
    vector<vector<char>> grid = {
    {'0', '0', '0', '1', '1', '1', '0', '0'},
    {'0', '0', '0', '1', '1', '1', '0', '0'},
    {'0', '0', '0', '0', '0', '0', '0', '0'},
    {'0', '0', '0', '0', '0', '1', '1', '1'},
    {'0', '0', '0', '0', '0', '1', '1', '1'},
    {'0', '1', '1', '0', '0', '0', '0', '0'},
    {'1', '1', '1', '0', '0', '0', '0', '0'},
    {'0', '1', '1', '0', '0', '0', '0', '0'}    
    };
    
    Solution s;
    cout<<s.numIslands(grid)<<endl;
    
    return 0;
}
