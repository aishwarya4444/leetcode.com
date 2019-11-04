/*

https://leetcode.com/problems/brace-expansion/

A string S represents a list of words.

Each letter in the word has 1 or more options.  If there is one option, the letter is represented as is.  If there is more than one option, then curly braces delimit the options.  For example, "{a,b,c}" represents options ["a", "b", "c"].

For example, "{a,b,c}d{e,f}" represents the list ["ade", "adf", "bde", "bdf", "cde", "cdf"].

Return all words that can be formed in this manner, in lexicographical order.



Example 1:

Input: "{a,b}c{d,e}f"
Output: ["acdf","acef","bcdf","bcef"]
Example 2:

Input: "abcd"
Output: ["abcd"]


Note:

1 <= S.length <= 50
There are no nested curly brackets.
All characters inside a pair of consecutive opening and ending curly brackets are different.

*/

class Solution {
public:
    vector<string> expand(string S) {
        vector<char> options;
        queue<string> res;
        vector<string> result;
        string word = "";
        int n, i;
        bool hasOption = false;

        res.push(word);

        for(auto chr: S) {
            if(chr == '{') {
                hasOption = true;
                continue;
            } else if(chr == '}') {
                hasOption = false;
                // populate all options
                n = res.size();
                while(n--) {
                    word = res.front();
                    res.pop();
                    for(i=0; i<options.size(); i++) {
                        chr = options[i];
                        res.push(word+chr);
                    }
                }
                options.clear();
                continue;
            }

            if(chr == ',') {
                continue;
            }

            if(hasOption) {
                options.push_back(chr);
            } else {
                n = res.size();
                while(n--) {
                    word = res.front();
                    res.pop();
                    res.push(word+chr);
                }
            }
        }

        while(res.size()) {
            result.push_back(res.front());
            res.pop();
        }

        sort(result.begin(), result.end());

        return result;
    }
};
