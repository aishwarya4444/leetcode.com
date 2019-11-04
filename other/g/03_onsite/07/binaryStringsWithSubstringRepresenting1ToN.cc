/*

https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/

Given a binary string S (a string consisting only of '0' and '1's) and a positive integer N, return true if and only if for every integer X from 1 to N, the binary representation of X is a substring of S.



Example 1:

Input: S = "0110", N = 3
Output: true
Example 2:

Input: S = "0110", N = 4
Output: false


Note:

1 <= S.length <= 1000
1 <= N <= 10^9

*/

class Solution {
public:
    bool queryString(string S, int N) {
        string result;
        int n;
        for(N; N>0; N--) {
            n = N;
            result = "";
            while(n) {
                if(n&1) {
                    result = '1'+result;
                } else {
                    result = '0'+result;
                }
                n >>= 1;
            }
            if(S.find(result) == string::npos) {
                return false;
            }
        }
        return true;
    }
};
