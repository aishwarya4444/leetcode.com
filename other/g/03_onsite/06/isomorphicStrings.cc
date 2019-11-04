/*

https://leetcode.com/problems/isomorphic-strings/

Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

Example 1:

Input: s = "egg", t = "add"
Output: true
Example 2:

Input: s = "foo", t = "bar"
Output: false
Example 3:

Input: s = "paper", t = "title"
Output: true
Note:
You may assume both s and t have the same length.

*/

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size()) {
            return false;
        }
        char parent, child;
        unordered_map<char, char> m1, m2;
        int i;
        for(i=0; i<s.size(); i++) {
            parent = s[i];
            child = t[i];
            if(m1.find(parent) == m1.end()) {
                m1[parent] = child;
            } else if(m1[parent] != child) {
                return false;
            }

            if(m2.find(child) == m2.end()) {
                m2[child] = parent;
            } else if(m2[child] != parent) {
                return false;
            }
        }
        return true;
    }
};

/*

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        map<char, set<char>> m1, m2;
        int n, n1=s.size(), n2=t.size();

        if(n1 != n2) {
            return false;
        }

        for(n=0; n<n1; n++) {
            m1[s[n]].insert(t[n]);
            m2[t[n]].insert(s[n]);
        }

        if((int)m1.size() != (int)m2.size()) {
            return false;
        }

        for(auto entry: m1) {
            if(entry.second.size() > 1) {
                return false;
            }
        }

        for(auto entry: m2) {
            if(entry.second.size() > 1) {
                return false;
            }
        }

        return true;
    }
};

*/
