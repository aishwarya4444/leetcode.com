/*

https://leetcode.com/problems/valid-mountain-array/

Given an array A of integers, return true if and only if it is a valid mountain array.

Recall that A is a mountain array if and only if:

A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[A.length - 1]




Example 1:

Input: [2,1]
Output: false
Example 2:

Input: [3,5,5]
Output: false
Example 3:

Input: [0,3,2,1]
Output: true


Note:

0 <= A.length <= 10000
0 <= A[i] <= 10000

*/

class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        int start=0, N=A.size();
        while(start<N-1) {
            if(A[start]<A[start+1]) {
                start++;
            } else if(A[start]==A[start+1]) {
                return false;
            } else {
                break;
            }
        }
        if(start==N-1 || start==0) {
            return false;
        }
        while(start<N-1) {
            if(A[start]>A[start+1]) {
                start++;
            } else if(A[start]==A[start+1]) {
                return false;
            } else {
                break;
            }
        }
        return start==N-1;
    }
};
