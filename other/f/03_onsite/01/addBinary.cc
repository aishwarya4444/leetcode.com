/*

https://leetcode.com/problems/add-binary/

Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"

*/

class Solution {
public:
    string addBinary(string a, string b) {
        int la=a.size()-1, lb=b.size()-1, sum=0;
        string res="";
        char digits[] = {'0', '1'};

        while(la>=0 || lb>=0) {
            if(la>=0) {
                sum += (a[la]-'0');
                la--;
            }
            if(lb>=0) {
                sum += (b[lb]-'0');
                lb--;
            }
            res += digits[sum%2];
            sum /= 2;
        }

        if(sum) {
            res += digits[sum];
        }

        reverse(res.begin(), res.end());
        return res;
    }
};

/*
// 8ms 9.1MB
// 27.87% fast 56%memory

class Solution {
public:
    string addBinary(string a, string b) {
        int la=a.size()-1, lb=b.size()-1, sum=0;
        string res="";
        char digits[] = {'0', '1'};

        while(la>=0 || lb>=0) {
            if(la>=0) {
                sum += (a[la]-'0');
                la--;
            }
            if(lb>=0) {
                sum += (b[lb]-'0');
                lb--;
            }
            res = digits[sum%2] + res;
            sum /= 2;
        }

        if(sum) {
            res = digits[sum] + res;
        }

        return res;
    }
};

*/
