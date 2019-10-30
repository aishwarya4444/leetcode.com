/*

https://leetcode.com/problems/add-bold-tag-in-string/

Given a string s and a list of strings dict, you need to add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in dict. If two such substrings overlap, you need to wrap them together by only one pair of closed bold tag. Also, if two substrings wrapped by bold tags are consecutive, you need to combine them.
Example 1:
Input:
s = "abcxyz123"
dict = ["abc","123"]
Output:
"<b>abc</b>xyz<b>123</b>"
Example 2:
Input:
s = "aaabbcc"
dict = ["aaa","aab","bc"]
Output:
"<b>aaabbc</b>c"
Note:
The given dict won't contain duplicates, and its length won't exceed 100.
All the strings in input have length in range [1, 1000].

*/

class Solution {
public:
    string addBoldTag(string s, vector<string>& dict) {
        int start, index, length, n, N=s.size();
        vector<bool> isPresent(N, false);
        string result = "";

        for(auto str: dict) {
            index = s.find(str);
            while (index != string::npos) {
                for (n = index; n<index+str.size(); n++) {
                    isPresent[n] = true;
                }
                index = s.find(str,index+1);
            }
        }

        for(n=0; n<N; ) {
            if(isPresent[n]) {
                result += "<b>";
                while(n<N && isPresent[n]) {
                    result += s[n];
                    n++;
                }
                result += "</b>";
            } else {
                result += s[n];
                n++;
            }
        }

        return result;
    }
};


/*

// using TRIE

struct TrieNode {
    bool isWord;
    TrieNode *child[130];
    TrieNode() {;
        isWord = false;
        for(int i=0; i<130; i++) {
            child[i] = NULL;
        }
    }
};

class Solution {
private:
    TrieNode *root;

    void insert(string word) {
        TrieNode *curr = root;
        int index;
        for(auto chr: word) {
            index = chr;
            if(!curr->child[index]) {
                curr->child[index] = new TrieNode();
            }
            curr = curr->child[index];
        }
        curr->isWord = true;
    }

    int search(string word) {
        TrieNode *curr = root;
        int index, length=0, result=-1;
        for(auto chr: word) {
            length++;
            index = chr;
            if(!curr) {
                break;
            }
            if(!curr->child[index]) {
                return result;
            }
            curr = curr->child[index];
            if(curr->isWord) {
                result = length;
            }
        }
        return result;
    }
public:
    string addBoldTag(string s, vector<string>& dict) {
        int start, index, length, n, N=s.size();
        vector<bool> isPresent(N, false);
        string result = "";

        root = new TrieNode();

        for(auto word: dict) {
            insert(word);
        }

        for(n=0; n<N; n++) {
            index = search(s.substr(n));
            for(start=n; start<n+index; start++) {
                isPresent[start] = true;
            }
        }

        for(n=0; n<N; ) {
            if(isPresent[n]) {
                result += "<b>";
                while(n<N && isPresent[n]) {
                    result += s[n];
                    n++;
                }
                result += "</b>";
            } else {
                result += s[n];
                n++;
            }
        }

        return result;
    }
};

*/
