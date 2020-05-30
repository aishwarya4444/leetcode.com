/*
https://leetcode.com/problems/intersection-of-three-sorted-arrays/

Given three integer arrays arr1, arr2 and arr3 sorted in strictly increasing order, return a sorted array of only the integers that appeared in all three arrays.



Example 1:

Input: arr1 = [1,2,3,4,5], arr2 = [1,2,5,7,9], arr3 = [1,3,4,5,8]
Output: [1,5]
Explanation: Only 1 and 5 appeared in the three arrays.


Constraints:

1 <= arr1.length, arr2.length, arr3.length <= 1000
1 <= arr1[i], arr2[i], arr3[i] <= 2000

*/

// https://leetcode.com/problems/intersection-of-two-arrays/
class Solution {
public:
    // const keyword is important here
    vector<int> intersection(const vector<int>& nums1, const vector<int>& nums2) {
        int n1=0, n2=0, N1=nums1.size(), N2=nums2.size();
        vector<int> res;

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

    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        return intersection(arr3, intersection(arr1, arr2));
    }
};

/*
class Solution {
public:
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        unordered_map<int, int> m;
        vector<int> res;

        for(int num: arr1) {
            m[num]++;
        }
        for(int num: arr2) {
            m[num]++;
        }
        for(int num: arr3) {
            m[num]++;
        }

        for(auto entry: m) {
            if(entry.second == 3) {
                res.push_back(entry.first);
            }
        }

        sort(res.begin(), res.end());

        return res;
    }
};
*/