/*

https://leetcode.com/problems/shortest-way-to-form-string/

From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).

Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target. If the task is impossible, return -1.



Example 1:

Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".
Example 2:

Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.
Example 3:

Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".


Constraints:

Both the source and target strings consist of only lowercase English letters from "a"-"z".
The lengths of source and target string are between 1 and 1000.

*/

class Solution {
public:
    int shortestWay(string source, string target) {
        int s=0, t=0, S=source.size(), T=target.size(), count=0, targetStart;
        while(t<T) {
            targetStart = t;
            s = 0;
            while(s<S && t<T) {
                if(source[s]==target[t]) {
                    s++;
                    t++;
                } else {
                    s++;
                }
            }
            // no match was found for current character in target string
            if(t==targetStart) {
                return -1;
            }
            count++;
        }
        return count;
    }
};

/*

// time complexity too large

class Solution {
public:
    void findLCS(string s, string t, queue<int> &len, bool &possible) {
        int r, c, S=s.size(), T=t.size();
        vector<vector<int> > dp(S+1, vector<int>(T+1, 0));

        for(r=1; r<=S; r++) {
            for(c=1; c<=T; c++) {
                if(s[r-1]==t[c-1]) {
                    dp[r][c] = 1+dp[r-1][c-1];
                } else {
                    dp[r][c] = max(dp[r-1][c], dp[r][c-1]);
                }
            }
        }

        for(r=S, c=1; c<=T; c++) {
            if(dp[r][c]!=c) {
                break;
            }
        }
        c--;
        if(c==0) {
            possible = false;
            return;
        }
        len.push(c);
        if(c==T) {
            return;
        }
        findLCS(s, t.substr(c), len, possible);

    }
    int shortestWay(string source, string target) {
        bool possible = true;
        queue<int> len;
        findLCS(source, target, len, possible);
        if(!possible) {
            return -1;
        }
        return len.size();
    }
};

*/
