/*

https://leetcode.com/problems/valid-palindrome-ii/

Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
Note:
The string will only contain lowercase characters a-z. The maximum length of the string is 50000.

*/

// https://leetcode.com/problems/valid-palindrome-iii/

class Solution {
private:
    vector<vector<int> > dp;
public:
    int palin(string &s, int l, int r) {
        if(l>r) return 0;
        if(l==r) return 1;

        if(dp[l][r] != -1) {
            return dp[l][r];
        }

        int c1=0, c2=0, c3=0;
        if(s[l]==s[r]) {
            c1 = 2+palin(s, l+1, r-1);
        }
        c2 = palin(s, l, r-1);
        c3 = palin(s, l+1, r);

        dp[l][r] = max(c1, max(c2, c3));
        return dp[l][r];
    }

//     bool validPalindrome(string s) {
//         int N=s.size(), palLen;

//         dp = vector(N, vector<int>(N, -1));
//         palLen = palin(s, 0, N-1);
//         if(N-palLen<=1) return true;
//         else return false;
//     }

    bool validPalindrome(string s) {
        int l=0, r=s.size()-1;
        while(l<r) {
            if(s[l]==s[r]) {
                l++;
                r--;
                continue;
            }

            return checkPalin(s, l+1, r) || checkPalin(s, l, r-1);
        }
        return true;
    }

    bool checkPalin(string &s, int l, int r) {
        while(l<r) {
            if(s[l]==s[r]) {
                l++;
                r--;
                continue;
            }
            return false;
        }
        return true;
    }
};
