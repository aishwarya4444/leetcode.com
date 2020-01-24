/*

https://leetcode.com/problems/add-and-search-word-data-structure-design/

Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.

*/

class WordDictionary {
private:
    struct TrieNode {
        TrieNode *letter[26];
        bool isWord;
        TrieNode() {
            isWord = false;
            for(int i=0; i<26; i++) {
                letter[i] = NULL;
            }
        }
    };

    TrieNode *root;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }

    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode *node = root;
        int num;

        for(auto chr: word) {
            if(chr>='A' && chr<='Z') {
                chr += 32;
            }
            num = chr-'a';
            if(!node->letter[num]) {
                node->letter[num] = new TrieNode();
            }
            node = node->letter[num];
        }
        node->isWord = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        queue<TrieNode*> q;
        int num, N;
        TrieNode *node;

        q.push(root);

        for(auto chr: word) {
            if(chr>='A' && chr<='Z') {
                chr += 32;
            }
            N = q.size();
            while(N--) {
                node = q.front();
                q.pop();

                if(chr == '.') {
                    for(int i=0; i<26; i++) {
                        if(node->letter[i]) {
                            q.push(node->letter[i]);
                        }
                    }
                } else {
                    num = chr-'a';
                    if(node->letter[num]) {
                        node = node->letter[num];
                        q.push(node);
                    }
                }
            }
        }
        while(q.size()) {
            node = q.front();
            q.pop();
            if(node->isWord) {
                return true;
            }
        }
        return false;
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
