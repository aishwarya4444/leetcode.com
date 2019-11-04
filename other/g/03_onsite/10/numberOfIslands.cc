/*

https://leetcode.com/problems/number-of-islands/

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1
Example 2:

Input:
11000
11000
00100
00011

Output: 3

*/

// using union-find

class Solution {
public:
    int find(vector<int> &p, int n) {
        if(p[n]==n) {
            return n;
        }
        return p[n] = find(p, p[n]);
    }

    bool outsideGrid(int r, int c, int m, int n) {
        if(r<0 || c<0 || r>=m || c>=n) {
            return true;
        }
        return false;
    }

    int numIslands(vector<vector<char>>& grid) {
        vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        int m=grid.size(), n=m?grid[0].size():0;
        int row, col, r, c, n1, n2, p1, p2, count=0;
        vector<int> p(m*n, -1), result;

        for(row=0; row<m; row++) {
            for(col=0; col<n; col++) {
                if(grid[row][col] == '0') {
                    continue;
                }
                n1 = row*n+col;

                p[n1] = n1;
                count++;

                for(auto dir: dirs) {
                    r = row+dir[0];
                    c = col+dir[1];
                    n2 = r*n+c;

                    if(outsideGrid(r, c, m, n) || p[n2] == -1) {
                        continue;
                    }

                    p1 = find(p, n1);
                    p2 = find(p, n2);

                    if(p1 != p2) {
                        // both work
                        // p[p1] = p2
                        p[p2] = p1;
                        count--;
                    }
                }
            }
        }

        return count;
    }
};

/*

// using DFS

class Solution {
public:
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int r, int c, int &R, int &C) {
        if(r<0 || r>=R || c<0 || c>=C || grid[r][c] == '0' || visited[r][c]) {
            return;
        }
        visited[r][c] = true;
        int i, _r, _c;
        for(i=0; i<4; i++) {
            _r = r+dir[i][0];
            _c = c+dir[i][1];
            dfs(grid, visited, _r, _c, R, C);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int count=0, r, c, R=grid.size(), C=R?grid[0].size():0;
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                if(grid[r][c] == '1' && !visited[r][c]) {
                    dfs(grid, visited, r, c, R, C);
                    count++;
                }
            }
        }
        return count;
    }
};

*/
