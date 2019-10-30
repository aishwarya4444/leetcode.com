/*

https://leetcode.com/problems/wiggle-sort/

Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

Example:

Input: nums = [3,5,2,1,6,4]
Output: One possible answer is [3,5,1,6,2,4]

*/

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n, N=nums.size()-1;
        sort(nums.begin(), nums.end());
        for(n=1; n<N; n+=2) {
            swap(nums[n], nums[n+1]);
        }
    }
};
