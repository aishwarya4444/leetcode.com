/*

https://leetcode.com/problems/rotated-digits/

X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X.  Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number and become invalid.

Now given a positive number N, how many numbers X from 1 to N are good?

Example:
Input: 10
Output: 4
Explanation:
There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Note:

N  will be in range [1, 10000].

*/

class Solution {
public:
    bool check(int n) {
        int rem;
        bool result = false;
        while(n) {
            rem = n%10;
            n /= 10;
            if(rem==3 || rem==4 || rem==7) {
                return false;
            }
            if(rem==2 || rem==5 || rem==6 || rem==9) {
                result = true;
            }
        }
        return result;
    }

    int rotatedDigits(int N) {
        int count=0;
        for(int n=1; n<=N; n++) {
            if(check(n)) {
                count++;
            }
        }
        return count;
    }
};

// has a DP solution also
