/*

https://leetcode.com/problems/valid-palindrome/

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true
Example 2:

Input: "race a car"
Output: false

*/

class Solution {
public:
    bool isPalindrome(string s) {
        int l=0, r=s.size()-1;
        char left, right;

        while(l<r) {
            while(s[l]<'0' || (s[l]>'9' && s[l]<65) || (s[l]>90 && s[l]<97) || s[l]>122) {
                l++;
                if(l>=r) return true;
            }
            while(s[r]<'0' || (s[r]>'9' && s[r]<65) || (s[r]>90 && s[r]<97) || s[r]>122) {
                r--;
                if(l>=r) return true;
            }

            left = s[l];
            right = s[r];

            if(left>=65 && left<=90) {
                left += 32;
            }

            if(right>=65 && right<=90) {
                right += 32;
            }

            if(left != right) {
                return false;
            }

            l++;
            r--;
        }

        return true;

    }
};
