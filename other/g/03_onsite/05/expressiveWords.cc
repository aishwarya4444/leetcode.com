/*

https://leetcode.com/problems/expressive-words/

Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", "hi" -> "hiiii".  In these strings like "heeellooo", we have groups of adjacent letters that are all the same:  "h", "eee", "ll", "ooo".

For some given string S, a query word is stretchy if it can be made to be equal to S by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is 3 or more.

For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has size less than 3.  Also, we could do another extension like "ll" -> "lllll" to get "helllllooo".  If S = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = S.

Given a list of query words, return the number of words that are stretchy.



Example:
Input:
S = "heeellooo"
words = ["hello", "hi", "helo"]
Output: 1
Explanation:
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.


Notes:

0 <= len(S) <= 100.
0 <= len(words) <= 100.
0 <= len(words[i]) <= 100.
S and all words in words consist only of lowercase letters

*/

class Solution {
public:
    int expressiveWords(string S, vector<string>& words) {
        int count=0;
        for(auto word: words) {
            if(check(word, S)) {
                count++;
            }
        }
        return count;
    }

    bool check(string a, string b) {
        // convert a to b
        int A=a.size(), B=b.size();
        int i1=0, i2=0, c1, c2;
        while(i1<A && i2<B) {
            c1=1;
            c2=1;
            if(a[i1] != b[i2]) {
                return false;
            }
            while(i1<A && a[i1]==a[i1+1]) {
                i1++;
                c1++;
            }
            while(i2<B && b[i2]==b[i2+1]) {
                i2++;
                c2++;
            }
            if(c1!=c2 && (c1>c2 || c2<3)) {
                return false;
            }
            i1++;
            i2++;
        }
        return i1==A && i2==B;
    }
};
