/*

https://leetcode.com/problems/stream-of-characters/

Implement the StreamChecker class as follows:

StreamChecker(words): Constructor, init the data structure with the given words.
query(letter): returns true if and only if for some k >= 1, the last k characters queried (in order from oldest to newest, including this letter just queried) spell one of the words in the given list.


Example:

StreamChecker streamChecker = new StreamChecker(["cd","f","kl"]); // init the dictionary.
streamChecker.query('a');          // return false
streamChecker.query('b');          // return false
streamChecker.query('c');          // return false
streamChecker.query('d');          // return true, because 'cd' is in the wordlist
streamChecker.query('e');          // return false
streamChecker.query('f');          // return true, because 'f' is in the wordlist
streamChecker.query('g');          // return false
streamChecker.query('h');          // return false
streamChecker.query('i');          // return false
streamChecker.query('j');          // return false
streamChecker.query('k');          // return false
streamChecker.query('l');          // return true, because 'kl' is in the wordlist


Note:

1 <= words.length <= 2000
1 <= words[i].length <= 2000
Words will only consist of lowercase English letters.
Queries will only consist of lowercase English letters.
The number of queries is at most 40000.

*/

struct TrieNode {
public:
    TrieNode *child[26];
    bool isWord;
    TrieNode() {
        for(int i=0; i<26; i++) {
            child[i] = NULL;
        }
        isWord = NULL;
    }
};

class StreamChecker {
private:
    TrieNode *root;
    string queryStr;

    void insert(string word) {
        TrieNode *curr = root;
        int index, n, N=word.size();
        for(n=N-1; n>=0; n--) {
            index = word[n]-'a';
            if(!curr->child[index]) {
                curr->child[index] = new TrieNode();
            }
            curr = curr->child[index];
        }
        curr->isWord = true;
    }
public:
    StreamChecker(vector<string>& words) {
        root = new TrieNode();
        queryStr = "";

        for(auto word: words) {
            insert(word);
        }
    }

    bool query(char letter) {
        TrieNode *curr = root;
        int index, n, N;
        queryStr += letter;
        N = queryStr.size();
        for(n=N-1; n>=0; n--) {
            index = queryStr[n]-'a';
            if(curr->child[index]) {
                curr = curr->child[index];
                if(curr->isWord) {
                    return true;
                }
            } else {
                break;
            }
        }
        return false;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
