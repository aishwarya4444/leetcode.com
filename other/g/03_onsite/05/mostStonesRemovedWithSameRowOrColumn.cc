/*

https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/

On a 2D plane, we place stones at some integer coordinate points.  Each coordinate point may have at most one stone.

Now, a move consists of removing a stone that shares a column or row with another stone on the grid.

What is the largest possible number of moves we can make?



Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Example 2:

Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Example 3:

Input: stones = [[0,0]]
Output: 0


Note:

1 <= stones.length <= 1000
0 <= stones[i][j] < 10000

*/

class Solution {
private:
    int _find(vector<int> &p, int n) {
        if(p[n] == n) {
            return n;
        }
        return p[n] = _find(p, p[n]);
    }

    void _union(vector<int> &p, int n1, int n2) {
       p[_find(p, n2)] = _find(p, n1);
    }

    void _makeSet(vector<int> &p) {
        for(int i=0; i<p.size(); i++) {
            p[i] = i;
        }
    }

public:
    int removeStones(vector<vector<int>>& stones) {
        vector<int> p(20000, -1);
        set<int> roots;

        _makeSet(p);

        for(auto stone: stones) {
            _union(p, stone[0], 10000+stone[1]);
        }

        for(auto stone: stones) {
            roots.insert(_find(p, stone[0]));
        }

        return stones.size()-roots.size();
    }
};
