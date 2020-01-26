/*

https://leetcode.com/problems/divide-two-integers/

Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Note:

Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem, assume that your function returns 2^31 − 1 when the division result overflows.

*/

// Solution 1
class Solution {
public:
    int divide(int dividend, int divisor) {
        int sign = (dividend<0 ^ divisor<0) ? -1 : 1;

        if(divisor==0) return INT_MAX;
        if(divisor==1) return dividend;
        if(divisor==-1) {
            if(dividend==INT_MIN) return INT_MAX;
            else return -dividend;
        }

        int count = 0;
        long long num = labs(dividend), den = labs(divisor);

        while(num>=den) {
            long long d = den;
            int c = 1;
            while(num >= d<<1) {
                d = d<<1;
                c = c<<1;
            }
            num -= d;
            count += c;
        }

        return sign*count;
    }
};

// Solution 2
// Time Complexity way more
class Solution {
public:
    int divide(int dividend, int divisor) {
        long long int num=dividend, den=divisor, count=0, prev;
        bool negative=false;
        long long int res=0;

        if(num<0 ^ den<0) {
            negative = true;
        }

        if(num<0) {
            num = -num;
        }

        if(den<0) {
            den = -den;
        }

        if(den == 1) {
            if(negative && num>INT_MAX) return INT_MIN;
            if(negative) return -num;
            return num>INT_MAX ? INT_MAX : num;
        }
        prev = den;

        if(num>=den) {
            count = 1;
        } else {
            return 0;
        }

        while(num>=den) {
            den *= 2;
            count *= 2;
        }

        while(den>num) {
            den -= prev;
            count--;
        }

        if(negative) {
            if(count>INT_MAX) {
                count = INT_MIN;
            } else {
                count = -count;
            }
        } else {
            if(count>INT_MAX) {
                count = INT_MAX;
            }
        }

        return count;
    }
};
