/*

https://leetcode.com/problems/group-shifted-strings/

Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

Example:

Input: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Output:
[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]

*/

class Solution {
public:
    string getKey(string str) {
        string res = "";
        char oldChr = str[0], newChr;
        for(auto chr: str) {
            newChr = (chr-oldChr+26)%26 + 'a';
            res += newChr;
        }
        return res;
    }
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<vector<string>> res;
        unordered_map<string, vector<string> > keyVals;

        for(auto str: strings) {
            keyVals[getKey(str)].push_back(str);
        }

        for(auto entry: keyVals) {
            res.push_back(entry.second);
        }

        return res;
    }
};
