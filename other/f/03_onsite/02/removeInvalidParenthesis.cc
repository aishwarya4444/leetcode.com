/*

https://leetcode.com/problems/remove-invalid-parentheses/

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Example 1:

Input: "()())()"
Output: ["()()()", "(())()"]
Example 2:

Input: "(a)())()"
Output: ["(a)()()", "(a())()"]
Example 3:

Input: ")("
Output: [""]

*/

class Solution {
private:
    unordered_set<string> result;

    void help(string &s, string tmp, int i, int left, int open, int close) {
        if(i==s.size()) {
            if(open==0 && close==0) {
                result.insert(tmp);
            }
            return;
        }

        if(s[i]=='(') {
            if(open>0) {
                help(s, tmp, i+1, left, open-1, close);
            }
            tmp.push_back(s[i]);
            help(s, tmp, i+1, left+1, open, close);
            tmp.pop_back();
        } else if(s[i]==')') {
            if(close>0) {
                help(s, tmp, i+1, left, open, close-1);
            }
            if(left>0) {
                tmp.push_back(s[i]);
                help(s, tmp, i+1, left-1, open, close);
                tmp.pop_back();
            }
        } else {
            tmp.push_back(s[i]);
            help(s, tmp, i+1, left, open, close);
            tmp.pop_back();
        }
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        int open=0, close=0;
        vector<string> res;
        string tmp="";

        for(auto chr: s) {
            if(chr=='(') {
                open++;
            } else if(chr==')') {
                if(open) open--;
                else close++;
            }
        }

        help(s, tmp, 0, 0, open, close);

        for(auto &str: result) {
            res.push_back(str);
        }

        return res;
    }
};
