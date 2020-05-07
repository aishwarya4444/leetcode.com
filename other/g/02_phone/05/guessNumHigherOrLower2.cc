/*

https://leetcode.com/problems/guess-number-higher-or-lower-ii/

We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.

However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.

Example:

n = 10, I pick 8.

First round:  You guess 5, I tell you that it's higher. You pay $5.
Second round: You guess 7, I tell you that it's higher. You pay $7.
Third round:  You guess 9, I tell you that it's lower. You pay $9.

Game over. 8 is the number I picked.

You end up paying $5 + $7 + $9 = $21.
Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.

*/

// Solution 1
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int> > dp(n+1, vector<int>(n+1, 0));
        int l, r, i, cost;

        for(l=n-1; l>=1; l--) {
            for(r=l+1; r<=n; r++) {
                if(r-l == 1) {
                    dp[l][r] = min(l, r);
                } else {
                    cost = INT_MAX;
                    for(i=l+1; i<=r-1; i++) {
                        cost = min(cost, i+max(dp[l][i-1], dp[i+1][r]) );
                    }
                    dp[l][r] = cost;
                }
            }
        }

        return dp[1][n];
    }
};

// Solution 2
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int> > dp(n+2, vector<int>(n+1, 0));
        int l, r, i, gap, cost;
        for(gap=1; gap<=n; gap++) {
            for(l=1; l<=n-gap; l++) {
                r = l+gap;
                if(gap==1) {
                    dp[l][r] = l;
                    continue;
                }
                cost = INT_MAX;
                for(i=l+1; i<=r-1; i++) {
                    cost = min(cost, i+max(dp[l][i-1], dp[i+1][r]));
                }
                dp[l][r] = cost;
            }
        }

        return dp[1][n];
    }
};
