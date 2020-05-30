/*
https://leetcode.com/problems/reverse-vowels-of-a-string/
Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:

Input: "hello"
Output: "holle"
Example 2:

Input: "leetcode"
Output: "leotcede"
Note:
The vowels does not include the letter "y".
*/

class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char> vowels;
        int start=0, end=s.size()-1;

        vowels.insert('a');
        vowels.insert('e');
        vowels.insert('i');
        vowels.insert('o');
        vowels.insert('u');
        vowels.insert('A');
        vowels.insert('E');
        vowels.insert('I');
        vowels.insert('O');
        vowels.insert('U');

        while(start<end) {
            while(start<end && vowels.count(s[start])==0) {
                start++;
            }
            while(start<end && vowels.count(s[end])==0) {
                end--;
            }
            if(start<end) {
                swap(s[start], s[end]);
                start++;
                end--;
            }
        }

        return s;
    }
};