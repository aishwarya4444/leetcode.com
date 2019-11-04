/*

https://leetcode.com/problems/sliding-puzzle/

On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, and an empty square represented by 0.

A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given a puzzle board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

Examples:

Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.
Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]
Input: board = [[3,2,4],[1,5,0]]
Output: 14
Note:

board will be a 2 x 3 array as described above.
board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].

*/

class Solution {
private:
    struct Node {
        int row, col;
        string board;
        Node(int r, int c, string b) {
            row = r;
            col = c;
            board = b;
        }
    };

public:
    int slidingPuzzle(vector<vector<int>>& board) {
        string start = "", nums = "0123456789", change = "", target = "123450";
        unordered_set<string> visited;
        int dirs[4][2] = {{-1,0}, {0,-1}, {1,0}, {0,1}};
        int level = 0, startIndex, changeIndex, n, row, col, r, c, R=board.size(), C=R?board[0].size():0;
        queue<Node> q;

        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                if(board[r][c] == 0) {
                    row = r;
                    col = c;
                }
                start += nums[board[r][c]];
            }
        }

        if(start == target) {
            return level;
        }

        q.push({row, col, start});
        while(q.size()) {
            n = q.size();
            level++;
            while(n--) {
                auto node = q.front();
                q.pop();
                start = node.board;
                row = node.row;
                col = node.col;
                startIndex = C*row + col;
                visited.insert(start);
                for(auto dir: dirs) {
                    change = start;
                    r = row+dir[0];
                    c = col+dir[1];
                    if(r<0 || c<0 || r>=R || c>=C) {
                        continue;
                    }
                    changeIndex = C*r + c;
                    change[startIndex] = start[changeIndex];
                    change[changeIndex] = nums[0];
                    if(visited.count(change) != 0) {
                        continue;
                    }
                    if(change == target) {
                        return level;
                    }
                    q.push({r, c, change});
                }
            }
        }

        return -1;
    }
};
