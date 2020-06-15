/*

https://leetcode.com/problems/intersection-of-two-arrays-ii/

Given two arrays, write a function to compute their intersection.

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Note:

Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:

What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

https://leetcode.com/problems/intersection-of-two-arrays/
https://leetcode.com/problems/intersection-of-three-sorted-arrays/

*/

// Solution 1
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int n1=0, n2=0, N1=nums1.size(), N2=nums2.size();
        vector<int> res;

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        while(n1<N1 && n2<N2) {
            if(nums1[n1]==nums2[n2]) {
                res.push_back(nums1[n1]);
                n1++;
                n2++;
            } else if(nums1[n1]<nums2[n2]) {
                n1++;
            } else {
                n2++;
            }
        }

        return res;
    }
};

// Solution 2
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m1;
        vector<int> res;

        for(auto num1: nums1) {
            m1[num1]++;
        }

        for(auto num2: nums2) {
            if(m1[num2]) {
                m1[num2]--;
                res.push_back(num2);
            }
        }

        return res;
    }
};
