/*

https://leetcode.com/problems/missing-ranges/

Given a sorted integer array nums, where the range of elements are in the inclusive range [lower, upper], return its missing ranges.

Example:

Input: nums = [0, 1, 3, 50, 75], lower = 0 and upper = 99,
Output: ["2", "4->49", "51->74", "76->99"]

*/

class Solution {
public:
    string merge(int start, int end) {
        if(start == end) {
            return to_string(start);
        } else {
            return to_string(start)+"->"+to_string(end);
        }
    }

    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        int n, N=nums.size(), s, e, start, end;
        vector<string> result;

        if(N==0) {
            start = lower;
            end = upper;
            result.push_back(merge(start, end));
            return result;
        }
        if(lower<nums[0]) {
            start = lower;
            end = nums[0]-1;
            result.push_back(merge(start, end));
        }
        for(n=1; n<N; n++) {
            if(nums[n-1]==nums[n] || nums[n-1]+1==nums[n]) {
                continue;
            }
            start = nums[n-1]+1;
            end = nums[n]-1;
            result.push_back(merge(start, end));
        }
        if(upper>nums[N-1]) {
            start = nums[N-1]+1;
            end = upper;
            result.push_back(merge(start, end));
        }
        return result;
    }
};
