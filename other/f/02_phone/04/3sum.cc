/*

https://leetcode.com/problems/3sum/

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int sum, i, j, k, N=nums.size(), num;
        vector<vector<int> > res;
        vector<int> r;

        sort(nums.begin(), nums.end());

        for(i=0; i<N-2; i++) {
            if(nums[i]>0) {
                break;
            }
            if(i>0 && nums[i]==nums[i-1]) {
                continue;
            }
            j = i+1;
            k = N-1;
            while(j<k) {
                sum = nums[i]+nums[j]+nums[k];
                if(sum == 0) {
                    r = {nums[i], nums[j], nums[k]};
                    res.push_back(r);
                    while(j<k && nums[k-1]==nums[k]) {
                        k--;
                    }
                    while(j<k && nums[j+1]==nums[j]) {
                        j++;
                    }
                    j++;
                    k--;
                } else if(sum > 0) {
                    k--;
                } else {
                    j++;
                }
            }
        }

        return res;
    }
};
