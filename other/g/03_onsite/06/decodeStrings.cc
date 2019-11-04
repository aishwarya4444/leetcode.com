/*

https://leetcode.com/problems/decode-string/

Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".

*/

class Solution {
public:
    // recursive descent
    string dfs(string &s, int &i) {
        string ans = "", temp = "";
        int count = 0;
        while(i<s.size()) {
            if(s[i]>='0' && s[i]<='9') {
                count = 10*count + (s[i] - '0');
                ++i;
            } else if(s[i]=='[') {
                temp = dfs(s, ++i);
                while(count--) {
                    ans += temp;
                }
                count = 0;
            } else if(s[i]==']') {
                ++i;
                return ans;
            } else {
                ans += s[i];
                ++i;
            }
        }
        return ans;
    }
    string decodeString(string s) {
        int i=0;
        return dfs(s, i);
    }
};
