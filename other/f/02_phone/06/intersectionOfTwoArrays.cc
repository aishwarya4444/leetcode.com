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

/*
comment : https://leetcode.com/problems/intersection-of-two-arrays/solution/
This is a Facebook interview question.
They ask for the intersection, which has a trivial solution using a hash or a set.

Then they ask you to solve it under these constraints:
O(n) time and O(1) space (the resulting array of intersections is not taken into consideration).
You are told the lists are sorted.

Cases to take into consideration include:
duplicates, negative values, single value lists, 0's, and empty list arguments.
Other considerations might include
sparse arrays.

https://leetcode.com/problems/intersection-of-three-sorted-arrays/
*/


// Solution 1
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        int n1=0, n2=0, N1=nums1.size(), N2=nums2.size();
        vector<int> res;

        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        while(n1<N1 && n2<N2) {
            while(n1<N1-1 && nums1[n1]==nums1[n1+1]) {
                n1++;
            }
            while(n2<N2-1 && nums2[n2]==nums2[n2+1]) {
                n2++;
            }

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
