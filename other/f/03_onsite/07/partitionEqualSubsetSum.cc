/*

https://leetcode.com/problems/partition-equal-subset-sum/

Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Note:

Each of the array element will not exceed 100.
The array size will not exceed 200.


Example 1:

Input: [1, 5, 11, 5]

Output: true

Explanation: The array can be partitioned as [1, 5, 5] and [11].


Example 2:

Input: [1, 2, 3, 5]

Output: false

Explanation: The array cannot be partitioned into equal sum subsets.

*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n, s, S=0, N=nums.size();
        for(auto num: nums) {
            S+=num;
        }
        if(S%2) {
            return false;
        }
        S/=2;
        bool dp[N][S+1] = {false};
        // vector<vector<bool> > dp(N, vector<bool>(S+1, false));
        for(n=0; n<N; n++) {
            dp[n][0] = true;
        }
        for(s=1; s<=S; s++) {
            dp[0][s] = s==nums[0];
        }
        for(n=1; n<N; n++) {
            for(s=1; s<=S; s++) {
                if(dp[n-1][s]) {
                    dp[n][s] = true;
                } else if(s>=nums[n]) {
                    dp[n][s] = dp[n-1][s-nums[n]];
                }
            }
        }
        return dp[N-1][S];
    }
};
