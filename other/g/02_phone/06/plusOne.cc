/*

https://leetcode.com/problems/plus-one/

Given a non-empty array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

Example 1:

Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Example 2:

Input: [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.

*/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int sum=1, n, N=digits.size();
        for(n=N-1; n>=0; n--) {
            sum += digits[n];
            digits[n] = sum%10;
            sum /= 10;
            if(sum==0) {
                break;
            }
        }
        if(sum) {
            digits.insert(digits.begin(), sum);
        }
        return digits;
    }
};
