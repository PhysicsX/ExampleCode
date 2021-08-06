#include <iostream>
#include <vector>
#include <queue>

// g++ -std=c++14 numberOfIslands.cpp -o numberOfIslands

using namespace std;

class Solution
{
	public:
		int numOfIsland(vector<vector<char>> vec)
		{
			
			int result = 0; // number of islands
			if(vec.size() == 0)
				return result;
			
			int numberOfRows = vec.size();
			int numberOfColumns = vec.at(0).size();
			vector<std::pair<int,int>> neighborCorr = {{0,1},{1,0},{0,-1},{-1,0}};

			for(int i=0; i<numberOfRows; i++)
			{
				for(int j=0; j<numberOfColumns; j++)
				{
					if(vec[i][j] == '1')
					{
						result++;
						queue<pair<int,int>> que;
						que.push({i,j});
						vec[i][j] = '0';

						while(!que.empty())
						{
							auto p = que.front();
							que.pop();

							for(const auto& coor : neighborCorr)
							{
							
								int x = p.first + coor.first;
								int y = p.second + coor.second;

								if(x>=0 && x<numberOfRows && y>=0 && y<numberOfColumns)
								{
									if(vec[x][y] == '1')
									{
										vec[x][y] = '0';
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
}; // end of the Solution Class		
int main()
{

        vector<vector<char>> grid = {

        {'0','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'1','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'1','0','0','0','0','0','0'},
        {'0','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'}

        };
        
        cout<<Solution().numOfIsland(grid)<<endl;

        return 1;
}


