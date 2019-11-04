/*

https://leetcode.com/problems/campus-bikes/

On a campus represented as a 2D grid, there are N workers and M bikes, with N <= M. Each worker and bike is a 2D coordinate on this grid.

Our goal is to assign a bike to each worker. Among the available bikes and workers, we choose the (worker, bike) pair with the shortest Manhattan distance between each other, and assign the bike to that worker. (If there are multiple (worker, bike) pairs with the same shortest Manhattan distance, we choose the pair with the smallest worker index; if there are multiple ways to do that, we choose the pair with the smallest bike index). We repeat this process until there are no available workers.

The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y - p2.y|.

Return a vector ans of length N, where ans[i] is the index (0-indexed) of the bike that the i-th worker is assigned to.



Example 1:



Input: workers = [[0,0],[2,1]], bikes = [[1,2],[3,3]]
Output: [1,0]
Explanation:
Worker 1 grabs Bike 0 as they are closest (without ties), and Worker 0 is assigned Bike 1. So the output is [1, 0].
Example 2:



Input: workers = [[0,0],[1,1],[2,0]], bikes = [[1,0],[2,2],[2,1]]
Output: [0,2,1]
Explanation:
Worker 0 grabs Bike 0 at first. Worker 1 and Worker 2 share the same distance to Bike 2, thus Worker 1 is assigned to Bike 2, and Worker 2 will take Bike 1. So the output is [0,2,1].


Note:

0 <= workers[i][j], bikes[i][j] < 1000
All worker and bike locations are distinct.
1 <= workers.length <= bikes.length <= 1000

*/

class Solution {
private:
    struct wbd {
        int w, b, d;
        wbd(int workerIndex, int bikeIndex, int dist) {
            w = workerIndex;
            b = bikeIndex;
            d = dist;
        }
    };

    struct compareWBD {
        bool operator()(wbd &p1, wbd &p2) {
            if(p1.d == p2.d) {
                if(p1.w == p2.w) {
                    return p1.b<p2.b;
                } else {
                    return p1.w<p2.w;
                }
            } else {
                return p1.d<p2.d;
            }
        }
    };
public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int dist, w, W=workers.size(), b, B=bikes.size();
        vector<wbd> dump;
        vector<int> res(W, -1);
        vector<bool> bikeUsed(B, false);

        if(B<W) {
            return res;
        }

        for(w=0; w<W; w++) {
            for(b=0; b<B; b++) {
                dist = abs(workers[w][0]-bikes[b][0])+abs(workers[w][1]-bikes[b][1]);
                dump.push_back({w, b, dist});
            }
        }

        sort(dump.begin(), dump.end(), compareWBD());

        for(auto node: dump) {
            w = node.w;
            b = node.b;
            // worker not assigned a bike
            if(res[w] == -1) {
                // bike not yet assigned
                if(!bikeUsed[b]) {
                    bikeUsed[b] = true;
                    res[w] = b;
                }
            }
        }
        return res;
    }
};
