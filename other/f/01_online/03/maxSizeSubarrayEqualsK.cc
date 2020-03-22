/*

https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/

Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

Example 1:

Input: nums = [1, -1, 5, -2, 3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
Example 2:

Input: nums = [-2, -1, 2, 1], k = 1
Output: 2
Explanation: The subarray [-1, 2] sums to 1 and is the longest.
Follow Up:
Can you do it in O(n) time?

*/

// https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/discuss/525847/Do-these-other-questions-first-before-trying-this-one

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        int sum=0, n, N=nums.size(), len=0;

        for(n=0; n<N; n++) {
            sum += nums[n];

            if(sum==k) {
                len=n+1;
            } else if(m.find(sum-k) != m.end()) {
                len = max(len, n-m[sum-k]);
            }

            if(m.find(sum) == m.end()) {
                m[sum] = n;
            }
        }

        return len;
    }
};

/*
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int start=0, end=0, N=nums.size(), len=-1, sum=0;
        for(start=0; start<N; start++) {
            sum=0;
            for(end=start; end<N; end++) {
                sum+=nums[end];
                if(sum==k) {
                    len=max(len, end-start+1);
                }
            }
        }
        return len==-1?0:len;
    }
};
*/
