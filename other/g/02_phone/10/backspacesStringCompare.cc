/*

https://leetcode.com/problems/backspace-string-compare/

Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
Note:

1 <= S.length <= 200
1 <= T.length <= 200
S and T only contain lowercase letters and '#' characters.
Follow up:

Can you solve it in O(N) time and O(1) space?

*/

class Solution {
public:
    bool backspaceCompare(string S, string T) {
        stack<char> s, t;

        for(auto chr: S) {
            if(chr=='#') {
                if(s.size()) {
                    s.pop();
                }
            } else {
                s.push(chr);
            }
        }

        for(auto chr: T) {
            if(chr=='#') {
                if(t.size()) {
                    t.pop();
                }
            } else {
                t.push(chr);
            }
        }

        if(s.size() != t.size()) {
            return false;
        }

        while(s.size()) {
            if(s.top()!=t.top()) {
                return false;
            }
            s.pop();
            t.pop();
        }

        return true;
    }
};

/*
// follow up
class Solution {
public:
  int getValidCharIndex(const string &str, int index) {
    int backspace = 0;
    while(index>=0) {
      if(str[index] == '#') {
        backspace++;
      } else if(backspace > 0) {
        backspace--;
      } else {
        break;
      }
      index--;
    }
    return index;
  }
  bool backspaceCompare(string S, string T) {
    int i1 = S.size()-1, i2 = T.size()-1;
    int c1 = 0, c2 = 0;
    while(i1>=0 || i2>=0) {

      c1 = getValidCharIndex(S, i1);
      c2 = getValidCharIndex(T, i2);

      if(c1<0 && c2<0) {
        return true;
      }

      if(c1<0 || c2<0) {
        return false;
      }

      if(S[c1] != T[c2]) {
        return false;
      }

      i1 = c1-1;
      i2 = c2-1;
    }
    return true;
  }
};
*/
