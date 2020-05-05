/*

https://leetcode.com/problems/letter-tile-possibilities/

You have a set of tiles, where each tile has one letter tiles[i] printed on it.  Return the number of possible non-empty sequences of letters you can make.



Example 1:

Input: "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
Example 2:

Input: "AAABBC"
Output: 188


Note:

1 <= tiles.length <= 7
tiles consists of uppercase English letters.

*/

// Solution 1
letter tile

class Solution {
public:
    int numTilePossibilities(string tiles) {
        vector<string> res;
        unordered_set<string> m;
        string word="", tmp;
        int n, N=tiles.size(), x, start, end;

        res.push_back(word);
        for(n=0; n<N; n++) {
            if(n>0 && tiles[n-1]==tiles[n]) {
                start = end;
            } else {
                start = 0;
            }
            end = res.size();
            for(start; start<end; start++) {
                word = res[start];
                for(x=0; x<=word.size(); x++) {
                    tmp = word;
                    tmp.insert(tmp.begin()+x, tiles[n]);

                    if(m.count(tmp) == 0) {
                        m.insert(tmp);
                        res.push_back(tmp);
                    }
                }
            }
        }
        // return m.size();
        return res.size()-1;
    }
};


// Solution 2
class Solution {
public:
    int numTilePossibilities(string tiles) {
        vector<string> res;
        unordered_map<string, bool> m;
        string word="", tmp;
        int n, N=tiles.size(), x, start, end;
        res.push_back(word);
        for(n=0; n<N; n++) {
            if(n>0 && tiles[n-1]==tiles[n]) {
                start = end;
            } else {
                start = 0;
            }
            end = res.size();
            for(start; start<end; start++) {
                word = res[start];
                for(x=0; x<=word.size(); x++) {
                    tmp = word;
                    tmp.insert(tmp.begin()+x, tiles[n]);

                    if(m.find(tmp) == m.end()) {
                        m[tmp] = true;
                        res.push_back(tmp);
                    }
                }
            }
        }
        return m.size();
    }
};
