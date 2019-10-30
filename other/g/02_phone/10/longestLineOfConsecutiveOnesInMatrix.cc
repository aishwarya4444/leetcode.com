/*

https://leetcode.com/problems/longest-line-of-consecutive-one-in-matrix/

Given a 01 matrix M, find the longest line of consecutive one in the matrix. The line could be horizontal, vertical, diagonal or anti-diagonal.
Example:
Input:
[[0,1,1,0],
 [0,1,1,0],
 [0,0,0,1]]
Output: 3
Hint: The number of elements in the given matrix will not exceed 10,000.

*/

class Solution {
public:
    int longestLine(vector<vector<int>>& M) {
        int count = 0, r, c, R=M.size(), C=R?M[0].size():R;
        vector<vector<int>> dp(R, vector<int>(C,0));

        // row wise
        for(r=0; r<R; r++) {
            dp[r][0] = M[r][0];
            count = max(count, dp[r][0]);
            for(c=1; c<C; c++) {
                if(M[r][c]) {
                    dp[r][c] = dp[r][c-1]+1;
                    count = max(count, dp[r][c]);
                }
            }
        }

        // clear
        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                dp[r][c] = 0;
            }
        }

        // column wise
        for(c=0; c<C; c++) {
            dp[0][c] = M[0][c];
            count = max(count, dp[0][c]);
            for(r=1; r<R; r++) {
                if(M[r][c]) {
                    dp[r][c] = dp[r-1][c]+1;
                    count=max(count, dp[r][c]);
                }
            }
        }

        // clear
        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                dp[r][c] = 0;
            }
        }

        // left diagonal wise
        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                if(!r || !c) {
                    dp[r][c] = M[r][c];
                    count = max(count, dp[r][c]);
                } else if(M[r][c]) {
                    dp[r][c] = dp[r-1][c-1]+1;
                    count=max(count, dp[r][c]);
                }
            }
        }

        // clear
        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                dp[r][c] = 0;
            }
        }

        // right diagonal wise
        for(r=0; r<R; r++) {
            for(c=C-1; c>=0; c--) {
                if(!r || c==C-1) {
                    dp[r][c] = M[r][c];
                    count = max(count, dp[r][c]);
                } else if(M[r][c]) {
                    dp[r][c] = dp[r-1][c+1]+1;
                    count=max(count, dp[r][c]);
                }
            }
        }

        return count;
    }
};
