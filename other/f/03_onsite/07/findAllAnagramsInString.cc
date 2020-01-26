/*

https://leetcode.com/problems/find-all-anagrams-in-a-string/

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

*/

class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    string str=s, pattern=p;
    vector<int> resultIndices;
    int start=0, end, S=str.size(), P=pattern.size(), match=0;
    unordered_map<char, int> freqMap;
    for(char chr: pattern) {
      freqMap[chr]++;
    }
    for(end=0; end<S; end++) {
      if(freqMap.find(str[end]) != freqMap.end()) {
        freqMap[str[end]]--;
        if(freqMap[str[end]] == 0) {
          match++;
        }
        if(match == (int)freqMap.size()) {
          resultIndices.push_back(start);
        }
      }
      if(end+1 >= P) {
        if(freqMap.find(str[start]) != freqMap.end()) {
          if(freqMap[str[start]] == 0) {
            match--;
          }
          freqMap[str[start]]++;
        }
        start++;
      }
    }
    return resultIndices;
  }
};
