/*

https://leetcode.com/problems/repeated-substring-pattern/

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.



Example 1:

Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.
Example 2:

Input: "aba"
Output: False
Example 3:

Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)

*/

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int i, n, N=s.size();
        string tmp;
        bool match;

        for(n=N/2; n>=1; n--) {
            tmp = s.substr(0, n);
            if(N%n == 0) {
                // match = true;
                // for(i=n; i<N; i+=n) {
                //     if(tmp != s.substr(i, n)) {
                //         match = false;
                //         break;
                //     }
                // }
                // if(match) {
                //     return true;
                // }
                string big;
                for(i=0; i<N/n; i++) {
                    big += tmp;
                }
                if(big == s) {
                    return true;
                }
            }
        }
        return false;
    }
};
