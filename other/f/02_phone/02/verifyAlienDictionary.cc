/*

https://leetcode.com/problems/verifying-an-alien-dictionary/

In an alien language, surprisingly they also use english lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.

Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographicaly in this alien language.



Example 1:

Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
Output: true
Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
Example 2:

Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
Output: false
Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.
Example 3:

Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
Output: false
Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).


Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 20
order.length == 26
All characters in words[i] and order are English lowercase letters.

*/

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        int n1, n2, j, n, N=words.size();
        string w1, w2;
        char c1, c2;

        for(n=1; n<N; n++) {
            w1 = words[n-1];
            w2 = words[n];

            n1 = w1.size();
            n2 = w2.size();

            for(j=0; j<min(n1, n2); j++) {
                c1 = w1[j];
                c2 = w2[j];
                if(c1 != c2) {
                    break;
                }
            }

            if(order.find(c1) > order.find(c2)) {
                return false;
            }

            if(c1==c2 && n1>n2) {
                return false;
            }
        }

        return true;
    }
};
