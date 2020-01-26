/*

https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

Say you have an array for which the i-th element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).

Example 1:

Input: [2,4,1], k = 2
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: [3,2,6,5,0,3], k = 2
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
             Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

*/

// https://www.youtube.com/watch?v=Pw6lrYANjz4

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int N=prices.size(), i, j, maxSoFar;
        if(prices.size()==0) {
            return 0;
        }

        // logic of https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
        // we can perform any number of transactions
        // more explanation in below question
        if(k >= N / 2) {
            int total_profit = 0;
            for(int i = 0; i < N-1; i++)
                if(prices[i] < prices[i+1])
                    total_profit += (prices[i+1] - prices[i]);

            return total_profit;
        }

        vector<vector<int> > dp(k+1, vector<int>(N, 0));

        for(i=1; i<=k; i++) {
            maxSoFar = INT_MIN;
            for(j=1; j<N; j++) {
                maxSoFar = max(maxSoFar, dp[i-1][j-1]-prices[j-1]);
                dp[i][j] = max(dp[i][j-1], maxSoFar+prices[j]);
            }
        }

        return dp[k][N-1];
    }
};

// Solution 2

/*
    We use state transition for this. Since there are k transactions, that means there are 2k states:
    One state when we have bought something and another when we have sold something.
    (Bought1)---sell---->(Sold1)-----buy----->(Bought2)------sell----->(Sold2)-----buy----->(Boughtk)------sell----->(Soldk)

    Also for each of the states, we can decide to not do anything, that would mean just using the
    current state.
    TC: O(Nk), SC: O(k)
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(prices.empty() || k == 0)
            return 0;

        const int N = prices.size();
        // to buy stock on ith day and sell on i+1th day takes N/2 transactions and repeating.
        // and need no order to decide when to buy or sell
        // So if k > N/2, then there is no need to decide when to buy or sell
        if(k >= N / 2) {
            int total_profit = 0;
            for(int i = 0; i < N-1; i++)
                if(prices[i] < prices[i+1])
                    total_profit += (prices[i+1] - prices[i]);

            return total_profit;
        }

        // states after buying and selling
        // bought(i): (i+1) state in the state transition,
        // each (except first) happens after a sold state
        vector<int> bought(k, INT_MIN);
        // sold(i): (i+2) state in state transition, each sold
        // state happens after (i+1)th bought(bought[i] in array) state
        vector<int> sold(k, INT_MIN);

        for(int i = 0; i < N; i++) {
            // first Bought and sold states
            bought[0] = max(bought[0], -prices[i]);
            sold[0] = max(sold[0], bought[0] + prices[i]);

            // update the remaining states
            for(int j = 1; j < k; j++) {
                // For each Bought state, either don't do anything or buy the current stock
                bought[j] = max(bought[j], sold[j-1] - prices[i]);
                // Either don't sell or sell the stock bought earlier
                sold[j] = max(sold[j], bought[j] + prices[i]);
            }
        }

        // final answer is the last sold state
        return sold.back();
    }
};
