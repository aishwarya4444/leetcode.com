/*

https://leetcode.com/problems/subarray-sum-equals-k/

Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:
Input:nums = [1,1,1], k = 2
Output: 2
Note:
The length of the array is in range [1, 20,000].
The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].

*/

// optimised
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // subarray sum equals K
        unordered_map<int,int>store;
        store[0] = 1;
        int sum = 0;
        int ans = 0;
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i];
            if(store.count(sum-k)){
                ans += store[sum-k];
            }
            store[sum]++;
        }
        return ans;
    }
};

// more time complexity
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count=0, start=0, end=0, N=nums.size();
        long long int sum=0;

        for(start=0; start<N; start++) {
            sum = 0;
            for(end=start; end<N; end++) {
                sum += nums[end];
                if(sum == k) {
                    count++;
                }
            }
        }

        return count;
    }
};
