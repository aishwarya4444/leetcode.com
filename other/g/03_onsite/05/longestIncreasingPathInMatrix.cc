/*

https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

Input: nums =
[
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].
Example 2:

Input: nums =
[
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

*/

class Solution {
public:
    int dfs(vector<vector<int>>& matrix, vector<vector<int>> &dp, vector<pair<int, int>> &dirs, int r, int c, int R, int C, int &maxLen) {
        int len=0, x, y, row, col;
        if(dp[r][c]>1) {
            return dp[r][c];
        }
        for(auto dir: dirs) {
            x = dir.first;
            y = dir.second;
            row = r+x;
            col = c+y;
            if(row>=0 && row<R && col>=0 && col<C && matrix[r][c]<matrix[row][col]) {
                len = dfs(matrix, dp, dirs, row, col, R, C, maxLen);
                dp[r][c] = max(len+1, dp[r][c]);
            }
        }
        maxLen = max(maxLen, dp[r][c]);
        return dp[r][c];
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int maxLen=0, r, c, R=matrix.size(), C=R?matrix[0].size():R;
        vector<vector<int>> dp = vector(R, vector<int>(C, 1));
        vector<pair<int, int>> dirs = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                dfs(matrix, dp, dirs, r, c, R, C, maxLen);
            }
        }
        return maxLen;
    }
};
