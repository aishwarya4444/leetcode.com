/*

https://leetcode.com/problems/decode-ways/

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given a non-empty string containing only digits, determine the total number of ways to decode it.

Example 1:

Input: "12"
Output: 2
Explanation: It could be decoded as "AB" (1 2) or "L" (12).
Example 2:

Input: "226"
Output: 3
Explanation: It could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

*/

class Solution {
public:
    bool isPossible(string s) {
        int n=stoi(s), N=s.size();
        if(N==1) {
            if(n>=1 && n<=9) {
                return true;
            } else {
                return false;
            }
        } else {
            if(n>=10 && n<=26) {
                return true;
            } else {
                return false;
            }
        }
    }
    int numDecodings(string s) {
        int N=s.size(), n;
        bool one, two;
        vector<int> dp(N+1, 0);

        dp[0] = 1;
        dp[1] = isPossible(s.substr(0, 1)) ? 1 : 0;

        for(n=2; n<=N; n++) {
            one = isPossible(s.substr(n-1, 1));
            two = isPossible(s.substr(n-2, 2));
            if(one) {
                dp[n] = dp[n-1];
            }
            if(two) {
                dp[n] += dp[n-2];
            }
        }

        return dp[N];
    }
};
