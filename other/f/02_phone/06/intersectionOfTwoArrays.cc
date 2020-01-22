/*

https://leetcode.com/problems/intersection-of-two-arrays/

Given two arrays, write a function to compute their intersection.

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
Note:

Each element in the result must be unique.
The result can be in any order.

*/

// comment : https://leetcode.com/problems/intersection-of-two-arrays/solution/
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> s1, s2;

        for(auto num: nums1) {
            s1.insert(num);
        }

        for(auto num: nums2) {
            if(s1.count(num) > 0) {
                s2.insert(num);
            }
        }

        return vector<int>(s2.begin(), s2.end());
    }
};
