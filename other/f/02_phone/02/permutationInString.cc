/*

https://leetcode.com/problems/permutation-in-string/

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.



Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False


Note:

The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].

*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> freq, _freq;
        int i, j, n1=s1.size(), n2=s2.size();
        bool found;

        for(auto chr: s1) {
            freq[chr]++;
        }

        for(i=0; i<=n2-n1; i++) {
            _freq = freq;
            found = true;
            for(j=i; j<i+n1; j++) {
                if(_freq[s2[j]] == 0) {
                    found = false;
                    break;
                }
                _freq[s2[j]]--;
            }
            if(found) return true;
        }

        return false;
    }
};

/*
class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    string str=s2, pattern=s1;
    int start=0, end, N=str.size(), match=0;
    unordered_map<char, int> patternFreq;
    for(char chr: pattern) {
      patternFreq[chr]++;
    }
    for(end=0; end<N; end++) {
      if(patternFreq.find(str[end]) != patternFreq.end()) {
        patternFreq[str[end]]--;
        if(patternFreq[str[end]] == 0) {
          match++;
        }
        if(match == (int)patternFreq.size()) {
          return true;
        }
      }
      if(end+1 >= pattern.size()) {
        if(patternFreq.find(str[start]) != patternFreq.end()) {
          if(patternFreq[str[start]]==0) {
            match--;
          }
          patternFreq[str[start]]++;
        }
        start++;
      }
    }
    return false;
  }
};
*/
