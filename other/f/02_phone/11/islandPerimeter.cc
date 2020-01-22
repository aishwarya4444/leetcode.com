/*

https://leetcode.com/problems/island-perimeter/

You are given a map in form of a two-dimensional integer grid where 1 represents land and 0 represents water.

Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes" (water inside that isn't connected to the water around the island). One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.



Example:

Input:
[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]

Output: 16

Explanation: The perimeter is the 16 yellow stripes in the image below:

*/

class Solution {
public:
    bool outside(int r, int c, int R, int C) {
        if(r<0 || c<0 || r==R || c==C) {
            return true;
        }
        return false;
    }
    int islandPerimeter(vector<vector<int>>& grid) {
        int r, c, R=grid.size(), C=R?grid[0].size():R;
        int row, col, per = 0;
        vector<vector<int> > dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};

        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                if(grid[r][c]) {
                    for(auto dir: dirs) {
                        row = r+dir[0];
                        col = c+dir[1];
                        if(outside(row, col, R, C) || grid[row][col]==0) {
                            per++;
                        }
                    }
                }
            }
        }

        return per;
    }
};
