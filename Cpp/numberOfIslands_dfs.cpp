#include <iostream>
#include <vector>

class Solution
{
	public:
		void dfs(std::vector<std::vector<char>> &map, int x, int y)
		{
			if(x < 0 || y < 0 || x >= map.size() || y >= map[0].size() || map[x][y] == '0')
				return;
				
			map[x][y] = '0';
			dfs(map, x + 1, y);			
			dfs(map, x - 1, y);
			dfs(map, x, y + 1);
			dfs(map, x, y - 1);
		}
		int numberOfIslands(std::vector<std::vector<char>> &map)
		{
			int result = 0;
			
			if(map.size() == 0)
				return result;
			
			for(int i = 0; i < map.size(); i++)
			{
				for(int j = 0; j < map[0].size(); j++)
				{
					if(map[i][j] == '1')
					{
						result ++;
						
						dfs(map,i,j);
					}
				}
			}
			
			
			return result;
		}
};


int main()
{
	
	std::vector<std::vector<char>> map 
	{
		{'1','0','1','0','1'},
		{'1','0','1','0','1'},
		{'1','0','1','0','1'},
		{'1','0','1','0','1'},
		{'1','0','0','0','0'},
		{'1','0','1','0','1'},
		{'1','0','0','0','1'},
		{'1','0','0','0','1'},
		{'1','0','0','0','1'},
		{'1','0','1','1','1'}
	};
	
	Solution s;
	std::cout<<s.numberOfIslands(map)<<std::endl;
}