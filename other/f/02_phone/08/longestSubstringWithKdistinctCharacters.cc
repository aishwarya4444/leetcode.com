/*

https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

Given a string, find the length of the longest substring T that contains at most k distinct characters.

Example 1:

Input: s = "eceba", k = 2
Output: 3
Explanation: T is "ece" which its length is 3.
Example 2:

Input: s = "aa", k = 1
Output: 2
Explanation: T is "aa" which its length is 2.

*/

class Solution {
public:
  int lengthOfLongestSubstringKDistinct(string s, int k) {
    int maxLength=0, start=0, end=0, N=s.size();
    unordered_map<char, int> m;
    for(end=0; end<N; end++) {
      m[s[end]]++;
      while((int)m.size()>k) {
        m[s[start]]--;
        if(m[s[start]]==0) {
          m.erase(s[start]);
        }
        start++;
      }
      maxLength = max(maxLength, end-start+1);
    }
    return maxLength;
  }
};
