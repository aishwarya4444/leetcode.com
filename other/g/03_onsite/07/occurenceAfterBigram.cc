/*

https://leetcode.com/problems/occurrences-after-bigram/

Given words first and second, consider occurrences in some text of the form "first second third", where second comes immediately after first, and third comes immediately after second.

For each such occurrence, add "third" to the answer, and return the answer.



Example 1:

Input: text = "alice is a good girl she is a good student", first = "a", second = "good"
Output: ["girl","student"]
Example 2:

Input: text = "we will we will rock you", first = "we", second = "will"
Output: ["we","rock"]


Note:

1 <= text.length <= 1000
text consists of space separated words, where each word consists of lowercase English letters.
1 <= first.length, second.length <= 10
first and second consist of lowercase English letters.

*/

class Solution {
public:
    vector<string> findOcurrences(string text, string first, string second) {
        vector<string> third;
        string word, search = ' '+first+' '+second+' ';
        text = ' '+text+' ';
        size_t n, N = text.size(), index = text.find(search);

        while(index != string::npos && index+search.size() < N) {
            text = text.substr(index + search.size());
            n = 0;
            while(n<N && text[n]==' ') {
                n++;
            }
            word = "";
            while(n<N && text[n]!=' ' && text[n]!='\0') {
                word += text[n];
                n++;
            }
            if(word.size()>0) {
                third.push_back(word);
            }
            text = ' '+text+' ';
            index = text.find(search);
        }
        return third;
    }
};
