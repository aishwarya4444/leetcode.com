/*

https://leetcode.com/problems/campus-bikes-ii/

On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.

We assign one unique bike to each worker so that the sum of the Manhattan distances between each worker and their assigned bike is minimized.

The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

Return the minimum possible sum of Manhattan distances between each worker and their assigned bike.



Example 1:



Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
Output: 6
Explanation:
We assign bike 0 to worker 0, bike 1 to worker 1. The Manhattan distance of both assignments is 3, so the output is 6.
Example 2:



Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
Output: 4
Explanation:
We first assign bike 0 to worker 0, then assign bike 1 to worker 1 or worker 2, bike 2 to worker 2 or worker 1. Both assignments lead to sum of the Manhattan distances as 4.


Note:

0 <= workers[i][0], workers[i][1], bikes[i][0], bikes[i][1] < 1000
All worker and bike locations are distinct.
1 <= workers.length <= bikes.length <= 10

*/

/*
https://leetcode.com/problems/campus-bikes-ii/discuss/363822/Clean-C%2B%2B-solution-97.52-in-speed-100-in-memory

https://algorithm-notes-allinone.blogspot.com/2019/09/leetcode-1066-campus-bikes-ii.html?showComment=1572543012641#c7941206181706365927

https://www.youtube.com/watch?v=5IZxLw_uJkY
*/

class Solution {
public:
    int dfs(vector<vector<int>>& workers, vector<vector<int>>& bikes, int wi, int bstate, vector<vector<int>> &dp) {
        if(wi == workers.size()) {
            return 0;
        }

        if(dp[wi][bstate] != -1) {
            return dp[wi][bstate];
        }

        int ans = INT_MAX, bike, manDist;
        for(int b=0; b<bikes.size(); b++) {
            bike = bstate | (1<<b);
            if(bike != bstate) {
                manDist = abs(workers[wi][0]-bikes[b][0]) + abs(workers[wi][1]-bikes[b][1]);
                manDist += dfs(workers, bikes, wi+1, bike, dp);
                ans = min(ans, manDist);
            }
        }

        dp[wi][bstate] = ans;
        return ans;
    }

    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int ans = INT_MAX, W=workers.size(), B=bikes.size();
        vector<bool> visited(bikes.size(), false);
        vector<vector<int>> dp(W, vector<int>(1<<B, -1));

        if(workers.size() > bikes.size()) {
            return -1;
        }

        return dfs(workers, bikes, 0, 0, dp);
    }
};

/*

// DFS solution .. TLE
class Solution {
public:
    int manDist(vector<int> &w, vector<int> &b) {
        return abs(w[0]-b[0])+abs(w[1]-b[1]);
    }

    void dfs(vector<vector<int>>& workers, vector<vector<int>>& bikes, int w, int dist, vector<bool> &visited, int &ans) {
        if(w == workers.size()) {
            ans = min(ans, dist);
            return;
        }

        if(dist >= ans) {
            return;
        }

        for(int b=0; b<bikes.size(); b++) {
            if(!visited[b]) {
                visited[b] = true;
                dfs(workers, bikes, w+1, dist+manDist(workers[w], bikes[b]), visited, ans);
                visited[b] = false;
            }
        }
    }

    int assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int ans = INT_MAX;
        vector<bool> visited(bikes.size(), false);

        if(workers.size() > bikes.size()) {
            return -1;
        }

        dfs(workers, bikes, 0, 0, visited, ans);
        return ans;
    }
};
*/
