/*
https://leetcode.com/problems/range-sum-query-immutable/
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.
*/

class NumArray {
private:
    vector<int> dp;
public:
    NumArray(vector<int>& nums) {
        int sum = 0;

        dp.push_back(sum);
        for(auto num: nums) {
            sum += num;
            dp.push_back(sum);
        }
    }

    int sumRange(int i, int j) {
        return dp[j+1]-dp[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */