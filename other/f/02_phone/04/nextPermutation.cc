/*

https://leetcode.com/problems/next-permutation/

Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int N=nums.size(), i=N-2, j=N-1;

        if(N<2) {
            return;
        }

        while(i>=0 && nums[i]>=nums[i+1]) {
            i--;
        }

        if(i>=0) {
            while(j>=0 && nums[i]>=nums[j]) {
                j--;
            }
            swap(nums[i], nums[j]);
        }

        reverse(nums.begin()+i+1, nums.end());
    }
};
