/*

https://leetcode.com/problems/perfect-squares/

Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:

Input: n = 12
Output: 3
Explanation: 12 = 4 + 4 + 4.
Example 2:

Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.

*/

class Solution {
public:
    int numSquares(int n) {
        vector<int> ps;
        int i=1, res;
        for(i=1; i*i<=n; i++) {
            ps.push_back(i*i);
        }


        int dp[ps.size()][n+1] = {INT_MAX};
        int r, c, c1, c2;
        for(c=0; c<=n; c++) {
            dp[0][c] = c;
        }
        for(r=0; r<ps.size(); r++) {
            dp[r][0] = 0;
        }
        for(r=1; r<ps.size(); r++) {
            for(c=1; c<=n; c++) {
                c1 = INT_MAX;
                c2 = INT_MAX;
                if(ps[r]<=c) {
                    c1 = 1+dp[r][c-ps[r]];
                }
                c2 = dp[r-1][c];
                dp[r][c] = min(c1, c2);
            }
        }
        return dp[ps.size()-1][n];
    }
};
