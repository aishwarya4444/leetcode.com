/*

https://leetcode.com/problems/fraction-to-recurring-decimal/

Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

Example 1:

Input: numerator = 1, denominator = 2
Output: "0.5"
Example 2:

Input: numerator = 2, denominator = 1
Output: "2"
Example 3:

Input: numerator = 2, denominator = 3
Output: "0.(6)"

*/

// https://leetcode.com/problems/fraction-to-recurring-decimal/discuss/51160/C%2B%2B-unordered_map

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        long n=labs(numerator), d=labs(denominator);
        string res="";
        unordered_map<long, int> nums;
        bool added=false;

        if((numerator<0 ^ denominator<0) && n) {
            res = '-';
        }

        if(n>=d) {
            res += to_string(n/d);
            n %= d;
        } else {
            res += to_string(0);
        }

        if(n) {
            res += '.';
            while(n) {
                if(nums.find(n) != nums.end()) {
                    res.insert(nums[n], "(");
                    res += ')';
                    break;
                }
                nums[n] = res.size();
                n *= 10;
                res += to_string(n/d);
                n %= d;
            }
        }

        return res;
    }
};
