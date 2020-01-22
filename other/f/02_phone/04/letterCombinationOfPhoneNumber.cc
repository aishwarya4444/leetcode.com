/*

https://leetcode.com/problems/letter-combinations-of-a-phone-number/

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.



Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
Note:

Although the above answer is in lexicographical order, your answer could be in any order you want.

*/

// ITERATIVE
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        queue<string> q;
        string str;
        int Q, digit, N=digits.size(), n;
        if(N==0) {
            return result;
        }
        string keypad[] = {" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        q.push("");
        for(char chr: digits) {
            digit = chr-'0';
            Q = q.size();
            while(Q--) {
                str = q.front();
                q.pop();
                for(char letter: keypad[digit]) {
                    q.push(str+letter);
                }
            }
        }
        while(q.size()) {
            result.push_back(q.front());
            q.pop();
        }
        return result;
    }
};

// RECURSIVE
class Solution {
public:
    void help(int i, vector<string> &m, string tmp, string &digits, vector<string> &res) {
        if(i==digits.size()) {
            if(tmp.size()) {
                res.push_back(tmp);
            }
            return;
        }
        for(auto chr: m[digits[i]-'0']) {
            help(i+1, m, tmp+chr, digits, res);
        }
    }

    vector<string> letterCombinations(string digits) {
        vector<string> res, m = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        string tmp="";
        help(0, m, tmp, digits, res);
        return res;
    }
};
