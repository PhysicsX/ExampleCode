#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

// g++ -std=c++14 numberOfIslands.cpp -o numberOfIslands

using namespace std;

class Solution
{
	public:
		int numOfIsland(vector<vector<char>> grid)
		{
			int m = grid.size(), n = m ? grid[0].size() : 0,
			islands = 0;
			int offsets[] = {0,1,0,-1,0};
			
			for(int i=0; i < m; i++)
			{
				for(int j=0; j < n; j++)
				{
					if(grid[i][j] == '1')
					{
						islands++; // increase the number of island when encounter with '1'
						grid[i][j] = '0'; // assign zero to explored coordinate
						queue<pair<int,int>> todo;
						todo.push({i,j});
						
						while(!todo.empty())
						{
							pair<int,int> p = todo.front();
							todo.pop();
							for(int k=0; k<4; k++)
							{
								int r = p.first + offsets[k], c = p.second + offsets[k+1];
								if(r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == '1')
								{
									grid[r][c] = '0';
									todo.push({r,c});
								}	
							}	
						}	
					}

				}
			
			}
			return islands;
		}
}; // end of the Solution Class		
int main()
{

        vector<vector<char>> grid = {

        {'0','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'1','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'1','0','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'}

        };
        Solution s;
        cout<<s.numOfIsland(grid)<<endl;

        return 1;
}


