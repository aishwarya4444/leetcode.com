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
        unordered_map<char, char> m;
        string res="";

        m['0']='0';
        m['1']='1';
        m['6']='9';
        m['8']='8';
        m['9']='6';

        for(auto chr: num) {
            if(chr=='2' || chr=='3' || chr=='4' || chr=='5' || chr=='7') {
                return false;
            }
            res = m[chr]+res;
        }

        return num==res;
    }
};
