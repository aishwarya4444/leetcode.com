/*

https://leetcode.com/problems/goat-latin/

A sentence S is given, composed of words separated by spaces. Each word consists of lowercase and uppercase letters only.

We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.)

The rules of Goat Latin are as follows:

If a word begins with a vowel (a, e, i, o, or u), append "ma" to the end of the word.
For example, the word 'apple' becomes 'applema'.

If a word begins with a consonant (i.e. not a vowel), remove the first letter and append it to the end, then add "ma".
For example, the word "goat" becomes "oatgma".

Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
For example, the first word gets "a" added to the end, the second word gets "aa" added to the end and so on.
Return the final sentence representing the conversion from S to Goat Latin.



Example 1:

Input: "I speak Goat Latin"
Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
Example 2:

Input: "The quick brown fox jumped over the lazy dog"
Output: "heTmaa uickqmaaa rownbmaaaa oxfmaaaaa umpedjmaaaaaa overmaaaaaaa hetmaaaaaaaa azylmaaaaaaaaa ogdmaaaaaaaaaa"


Notes:

S contains only uppercase, lowercase and spaces. Exactly one space between each word.
1 <= S.length <= 150.

*/

class Solution {
public:
    bool isVowel(char c) {
        if(c<91) {
            c = c+32;
        }
        if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u') {
            return true;
        }
        return false;
    }

    string convert(string &S, int l, int r, bool vowel, int freq) {
        string tmp;

        if(vowel) {
            tmp = S.substr(l, r-l+1);
        } else {
            tmp = S.substr(l+1, r-l) + S[l];
        }

        tmp = tmp  + "ma" + string(freq, 'a');

        return tmp;
    }

    string toGoatLatin(string S) {
        int count=0, i, n, N=S.size();
        bool vowel;
        string res="";

        for(n=0; n<N; n++) {
            i = n;
            vowel = isVowel(S[i]);
            count++;
            while(S[n]!='\0' && S[n]!=' ') {
                n++;
            }
            res = res + convert(S, i, n-1, vowel, count);
            if(n<N) {
                res += ' ';
            }
        }

        return res;
    }
};
