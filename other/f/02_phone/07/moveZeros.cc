/*

https://leetcode.com/problems/move-zeroes/

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations.

*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int l=0, r=0, N=nums.size(), count=0;
        while(r<N) {
            if(nums[r]==0) {
                count++;
                r++;
            } else {
                nums[l] = nums[r];
                l++;
                r++;
            }
        }

        r = N-1;
        while(count--) {
            nums[r] = 0;
            r--;
        }
    }
};
