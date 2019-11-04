/*

https://leetcode.com/problems/sentence-similarity/

Given two sentences words1, words2 (each represented as an array of strings), and a list of similar word pairs pairs, determine if two sentences are similar.

For example, "great acting skills" and "fine drama talent" are similar, if the similar word pairs are pairs = [["great", "fine"], ["acting","drama"], ["skills","talent"]].

Note that the similarity relation is not transitive. For example, if "great" and "fine" are similar, and "fine" and "good" are similar, "great" and "good" are not necessarily similar.

However, similarity is symmetric. For example, "great" and "fine" being similar is the same as "fine" and "great" being similar.

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
    bool areSentencesSimilar(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        unordered_set<string> pairSet;
        int n, N=words1.size();
        string w1, w2;

        if(N != words2.size()) {
            return false;
        }

        for(auto pair: pairs) {
            pairSet.insert(pair[0]+'_'+pair[1]);
        }

        for(n=0; n<N; n++) {
            w1 = words1[n];
            w2 = words2[n];

            if(w1 == w2) {
                continue;
            }

            if(pairSet.find(w1+'_'+w2) == pairSet.end() && pairSet.count(w2+'_'+w1) == 0) {
                return false;
            }
        }

        return true;

    }
};

/*
// AC but .. TC 20ms 12.19% ... SC 11.4MB 25.00%
class Solution {
public:
    bool areSentencesSimilar(vector<string>& words1, vector<string>& words2, vector<vector<string>>& pairs) {
        unordered_map<string, unordered_set<string>> pairMap;
        int n, N=words1.size();
        string w1, w2;

        if(N != words2.size()) {
            return false;
        }

        for(auto pair: pairs) {
            pairMap[pair[0]].insert(pair[1]);
            pairMap[pair[1]].insert(pair[0]);
        }

        for(n=0; n<N; n++) {
            w1 = words1[n];
            w2 = words2[n];

            if(w1 == w2) {
                continue;
            }

            if(pairMap[w1].find(w2) == pairMap[w2].end()) {
                return false;
            }
        }

        return true;
    }
};
*/
