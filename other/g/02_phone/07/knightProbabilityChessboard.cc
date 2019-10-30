/*

https://leetcode.com/problems/knight-probability-in-chessboard/

On an NxN chessboard, a knight starts at the r-th row and c-th column and attempts to make exactly K moves. The rows and columns are 0 indexed, so the top-left square is (0, 0), and the bottom-right square is (N-1, N-1).

A chess knight has 8 possible moves it can make, as illustrated below. Each move is two squares in a cardinal direction, then one square in an orthogonal direction.

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly K moves or has moved off the chessboard. Return the probability that the knight remains on the board after it has stopped moving.

Example:

Input: 3, 2, 0, 0
Output: 0.0625
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.

Note:

N will be between 1 and 25.
K will be between 0 and 100.
The knight always initially starts on the board.

*/

class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        vector<pair<int, int> > dirs = {{1,2}, {2,1}, {1,-2}, {2,-1}, {-1,-2}, {-2,-1}, {-1,2}, {-2,1}};
        vector<vector<double>> dp(N, vector<double>(N, 0));
        int x, y, row, col, k=K;
        double ans = 0;
        dp[r][c] = 1;
        while(k--) {
            vector<vector<double>> dp2(N, vector<double>(N, 0));
            for(row=0; row<N; row++) {
                for(col=0; col<N; col++) {
                    if(dp[row][col]==0) {
                        continue;
                    }
                    for(auto dir: dirs) {
                        x = dir.first+row;
                        y = dir.second+col;
                        if(x>=0 && x<N && y>=0 && y<N) {
                            dp2[x][y] += dp[row][col]/8.0;
                        }
                    }
                }
            }
            dp = dp2;
        }

        for(row=0; row<N; row++) {
            for(col=0; col<N; col++) {
                ans += dp[row][col];
            }
        }

        return ans;
    }
};

// MLE for 8,30,6,4
// class Solution {
// public:
//     double knightProbability(int N, int K, int r, int c) {
//         vector<pair<int, int> > dirs = {{1,2}, {2,1}, {1,-2}, {2,-1}, {-1,-2}, {-2,-1}, {-1,2}, {-2,1}};
//         queue<pair<int, int> > q;
//         pair<int, int> cell;
//         int level=0, x, y, valid=0, total=0;
//         q.push({r, c});
//         while(level<K) {
//             level++;
//             total = q.size();
//             while(total--) {
//                 cell = q.front();
//                 q.pop();
//                 x = cell.first;
//                 y = cell.second;
//                 for(auto dir: dirs) {
//                     r = x+dir.first;
//                     c = y+dir.second;
//                     if(r>=0 && r<N && c>=0 && c<N) {
//                         q.push({r, c});
//                     }
//                 }
//             }
//         }
//         total = pow(8.0, K);
//         valid = q.size();
//         return 1.0*valid/total;
//     }
// };
