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
			vector<int> neighborCorr = {0,1,0,-1,0};

			for(int i=0; i<numberOfRows; i++)
			{
				for(int j=0; j<numberOfColumns; j++)
				{
					if(vec.at(i).at(j) == '1')
					{
						result++;
						queue<pair<int,int>> que;
						que.push({i,j});
						vec.at(i).at(j) = '0';

						while(!que.empty())
						{
							auto p = que.front();
							que.pop();

							for(int k=0; k<neighborCorr.size(); k++)
							{
							
								int x = p.first + neighborCorr[k];
								int y = p.second + neighborCorr[k+1];

								if(x>=0 && x<numberOfRows && y>=0 && y<numberOfColumns)
								{
									if(vec.at(x).at(y) == '1')
									{
										vec.at(x).at(y) = '0';
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
        {'1','0','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'},
        {'0','1','0','1','1','1','0'}

        };
        Solution s;
        cout<<s.numOfIsland(grid)<<endl;

        return 1;
}


