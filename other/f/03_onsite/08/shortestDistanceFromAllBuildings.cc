/*

https://leetcode.com/problems/shortest-distance-from-all-buildings/

You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
Example:

Input: [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0

Output: 7

Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2),
             the point (1,2) is an ideal empty land to build a house, as the total
             travel distance of 3+3+1=7 is minimal. So return 7.
Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.

*/

class Solution {
private:
    struct State {
        int row, col, len;
        State(int r, int c, int l) {
            row = r;
            col = c;
            len = l;
        }
    };

public:
    int shortestDistance(vector<vector<int>>& grid) {
        int r, c, row, col, x, y, len, ones=0, total=INT_MAX;
        int R=grid.size(), C=R?grid[0].size():0, N;

        vector<vector<int> > distance(R, vector<int>(C, 0));
        vector<vector<int> > buildings(R, vector<int>(C, 0));
        vector<vector<bool> > visited;
        vector<vector<int> > dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        queue<State> q;

        // start from all 1's and try to reach all 0's
        // update distance and buildings in the process
        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                if(grid[r][c]==1) {
                    ones++;
                    q.push({r, c, 0});
                    visited = vector<vector<bool> > (R, vector<bool>(C, false));

                    while(q.size()) {
                        N = q.size();
                        while(N--) {
                            auto st = q.front();
                            q.pop();
                            row = st.row;
                            col = st.col;
                            len = st.len+1;

                            for(auto dir: dirs) {
                                x = row+dir[0];
                                y = col+dir[1];
                                if(x>=0 && x<R && y>=0 && y<C && !grid[x][y] && !visited[x][y]) {
                                    buildings[x][y]++;
                                    distance[x][y] += len;
                                    q.push({x, y, len});
                                    visited[x][y] = true;
                                }
                            }
                        }
                    }
                }
            }
        }

        // go through grid and find 0's which have been visited by all 1's
        // and have minimum distance
        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                if(!grid[r][c] && ones==buildings[r][c] && distance[r][c]>0) {
                    total = min(total,  distance[r][c]);
                }
            }
        }

        return total==INT_MAX ? -1 : total;
    }
};

/*
// Time Limit Exceeded
class Solution {
private:
    int R, C;
    unordered_map<int, vector< pair<int, int> > > m;
    vector<pair<int, int> > dirs;

public:
    int shortestDistance(vector<vector<int>>& grid) {
        int r, c, row, col, x, y, level, n, total, desCount, minDist = INT_MAX;
        bool found = false;

        R = grid.size();
        C = grid[0].size();

        dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};

        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                m[grid[r][c]].push_back({r, c});
            }
        }

        for(auto src: m[0]) {
            total = 0;
            desCount = 0;
            for(auto des: m[1]) {
                // destination
                row = des.first;
                col = des.second;

                vector<vector<bool> > visited(R, vector<bool>(C, false));
                queue<pair<int, int> > q;

                q.push(src);
                level = 0;
                found = false;

                while(q.size() && !found) {
                    n = q.size();
                    level++;
                    while(n-- && !found) {
                        r = q.front().first;
                        c = q.front().second;
                        q.pop();
                        visited[r][c] = true;

                        for(auto dir: dirs) {
                            x = r+dir.first;
                            y = c+dir.second;
                            if(!found && x>=0 && x<R && y>=0 && y<C && !visited[x][y] && grid[x][y]!=2) {
                                if(x==row && y==col) {
                                    found = true;
                                    desCount++;
                                    total += level;
                                    break;
                                }
                                if(grid[x][y]==0 && !visited[x][y]) {
                                    q.push({x, y});
                                }
                            }
                        }
                    }
                }

                if(!found) {
                    total = INT_MAX;
                    break;
                }
            }

            if(desCount == m[1].size()) {
                minDist = min(minDist, total);
            }
        }

        return minDist==INT_MAX ? -1 : minDist;
    }
};
*/
