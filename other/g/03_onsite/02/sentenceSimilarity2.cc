/*

https://leetcode.com/problems/sentence-similarity-ii/

Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.

For example, words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"], ["acting","drama"], ["skills","talent"]].

Note that the similarity relation is transitive. For example, if "great" and "good" are similar, and "fine" and "good" are similar, then "great" and "fine" are similar.

Similarity is also symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.

Also, a word is always similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are no specified similar word pairs.

Finally, sentences can only be similar if they have the same number of words. So a sentence like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].

Note:

The length of words1 and words2 will not exceed 1000.
The length of pairs will not exceed 2000.
The length of each pairs[i] will be 2.
The length of each words[i] and pairs[i][j] will be in the range [1, 20].

*/

class Solution {
public:
    int _find(vector<int> &p, int n) {
        if(p[n] == n) {
            return n;
        }
        return p[n] = _find(p, p[n]);
    }

    void _union(vector<int> &p, int n1, int n2) {
        p[_find(p, n2)] = _find(p, n1);
    }

    void makeSet(vector<int> &p) {
        for(int n=0; n<p.size(); n++) {
            p[n] = n;
        }
    }

    bool areSentencesSimilarTwo(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        unordered_map<string, int> wordId;
        vector<int> p(2*pairs.size(), -1);
        int count=0, n, N=words1.size();
        string w1, w2;

        if(N != words2.size()) {
            return false;
        }

        makeSet(p);

        for(auto pair: pairs) {
            if(wordId.find(pair[0]) == wordId.end()) {
                wordId[pair[0]] = count++;
            }
            if(wordId.find(pair[1]) == wordId.end()) {
                wordId[pair[1]] = count++;
            }
            _union(p, wordId[pair[0]], wordId[pair[1]]);
        }

        for(n=0; n<N; n++) {
            w1 = words1[n];
            w2 = words2[n];

            if(w1 == w2) {
                continue;
            }

            if(wordId.find(w1) == wordId.end() || wordId.find(w2) == wordId.end()) {
                return false;
            }
            if(_find(p, wordId[w1]) != _find(p, wordId[w2])) {
                return false;
            }
        }

        return true;
    }
};
