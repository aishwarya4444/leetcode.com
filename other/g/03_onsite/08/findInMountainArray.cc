/*

https://leetcode.com/problems/find-in-mountain-array/

(This problem is an interactive problem.)

You may recall that an array A is a mountain array if and only if:

A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[A.length - 1]
Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target.  If such an index doesn't exist, return -1.

You can't access the mountain array directly.  You may only access the array using a MountainArray interface:

MountainArray.get(k) returns the element of the array at index k (0-indexed).
MountainArray.length() returns the length of the array.
Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.



Example 1:

Input: array = [1,2,3,4,5,3,1], target = 3
Output: 2
Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
Example 2:

Input: array = [0,1,2,4,2,1], target = 3
Output: -1
Explanation: 3 does not exist in the array, so we return -1.


Constraints:

3 <= mountain_arr.length() <= 10000
0 <= target <= 10^9
0 <= mountain_arr.get(index) <= 10^9

*/

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */
class Solution {
private:
    int N;
public:

    int peakIndexInMountainArray(MountainArray &mountainArr) {
        int l=0, r=N-1, m, left, mid, right;
        while(l<=r) {
            m = l+(r-l)/2;
            left = mountainArr.get(m-1);
            mid = mountainArr.get(m);
            right = mountainArr.get(m+1);
            if(left<mid && mid>right) {
                return m;
            }
            if(mid>right) {
                r = m;
            } else if(left<mid) {
                l = m;
            }
        }
        return l;
    }

    int binSearchAsc(int l, int r, int target, MountainArray &mountainArr) {
        int m, left, mid, right;
        while(l<=r) {
            m = l+(r-l)/2;

            mid = mountainArr.get(m);
            if(mid == target) {
                return m;
            }
            if(mid < target) {
                l = m+1;
            } else {
                r = m-1;
            }
        }

        return -1;
    }

    int binSearchDesc(int l, int r, int target, MountainArray &mountainArr) {
        int m, left, mid, right;
        while(l<=r) {
            m = l+(r-l)/2;

            mid = mountainArr.get(m);
            if(mid == target) {
                return m;
            }
            if(mid > target) {
                l = m+1;
            } else {
                r = m-1;
            }
        }

        return -1;
    }

    int findInMountainArray(int target, MountainArray &mountainArr) {
        int index, leftIndex, rightIndex;
        N = mountainArr.length();

        index = peakIndexInMountainArray(mountainArr);
        leftIndex = binSearchAsc(0, index, target, mountainArr);
        if(leftIndex == -1) {
            return binSearchDesc(index+1, N-1, target, mountainArr);
        }
        return leftIndex;
    }
};
