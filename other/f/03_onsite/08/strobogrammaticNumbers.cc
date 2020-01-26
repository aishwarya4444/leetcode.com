/*

https://leetcode.com/problems/strobogrammatic-number/

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

Example 1:

Input:  "69"
Output: true
Example 2:

Input:  "88"
Output: true
Example 3:

Input:  "962"
Output: false

*/

class Solution {
public:
    bool isStrobogrammatic(string num) {
        unordered_map<char, char> mirror;
        string res;

        mirror['0'] = '0';
        mirror['1'] = '1';
        mirror['6'] = '9';
        mirror['9'] = '6';
        mirror['8'] = '8';

        for(auto chr: num) {
            if(mirror.find(chr) == mirror.end()) {
                return false;
            }
            res += mirror[chr];
        }

        reverse(res.begin(), res.end());

        return res==num;
    }
};
