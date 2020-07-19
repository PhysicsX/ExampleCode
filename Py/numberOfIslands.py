import collections


class Solution(object):
    def numOfIslands(self, grid):
        if not grid or not grid[0]:
            return 0
        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (0, -1), (-1, 0), (1, 0)]
        count = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '1':
                    count += 1
                    queue = collections.deque()
                    queue.append((i, j))
                    grid[i][j] = '0'
                    while queue:
                        r, c = queue.popleft()
                        for d in directions:
                            nr, nc = r + d[0], c + d[1]
                            if nr >= 0 and nr < m and nc >= 0 and nc < n and grid[nr][nc] == '1':
                                queue.append((nr, nc))
                                grid[nr][nc] = '0'
        return count


tmp = Solution()
grid = [
    ['1', '0', '1', '0', '1', '0', '1'],
    ['1', '0', '0', '0', '0', '0', '1'],
    ['0', '0', '0', '1', '0', '0', '1'],
    ['1', '0', '1', '0', '1', '1', '1'],
    ['1', '0', '1', '0', '1', '0', '1'],
    ['1', '0', '1', '0', '1', '0', '1']
]
print(tmp.numOfIslands(grid))
