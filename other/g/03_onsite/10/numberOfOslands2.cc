/*

https://leetcode.com/problems/number-of-islands-ii/

A 2d grid map of m rows and n columns is initially filled with water. We may perform an addLand operation which turns the water at position (row, col) into a land. Given a list of positions to operate, count the number of islands after each addLand operation. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example:

Input: m = 3, n = 3, positions = [[0,0], [0,1], [1,2], [2,1]]
Output: [1,1,2,3]
Explanation:

Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).

0 0 0
0 0 0
0 0 0
Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.

1 0 0
0 0 0   Number of islands = 1
0 0 0
Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.

1 1 0
0 0 0   Number of islands = 1
0 0 0
Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.

1 1 0
0 0 1   Number of islands = 2
0 0 0
Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.

1 1 0
0 0 1   Number of islands = 3
0 1 0
Follow up:

Can you do it in time complexity O(k log mn), where k is the length of the positions?

*/

/*
https://leetcode.com/problems/number-of-islands-ii/discuss/75485/C%2B%2B-union-find-solution-with-Path-Compression
*/

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

    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<vector<int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        int row, col, r, c, n1, n2, p1, p2, count=0;
        vector<int> p(m*n, -1), result;

        for(auto pos: positions) {
            row = pos[0];
            col = pos[1];
            n1 = row*n+col;

            // already added
            if(p[n1] != -1) {
                result.push_back(count);
                continue;
            }

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
            result.push_back(count);
        }

        return result;
    }
};

/*

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

    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        vector<int> result;
        vector<vector<char> > grid = vector(m, vector<char>(n, '0'));

        for(auto pos: positions) {
            grid[pos[0]][pos[1]] = '1';
            result.push_back(numIslands(grid));
        }

        return result;
    }
};

*/
