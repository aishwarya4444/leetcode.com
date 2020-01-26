/*

https://leetcode.com/problems/sparse-matrix-multiplication/

Given two sparse matrices A and B, return the result of AB.

You may assume that A's column number is equal to B's row number.

Example:

Input:

A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]

Output:

     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |

*/

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        // A = RxM
        // B = MxC

        int R=A.size(), M=B.size(), C=B[0].size();
        vector<vector<int> > res(R, vector<int>(C, 0));
        int r, c, i, sum;

        for(r=0; r<R; r++) {
            for(c=0; c<C; c++) {
                sum = 0;
                for(i=0; i<M; i++) {
                    sum += A[r][i]*B[i][c];
                }
                res[r][c] = sum;
            }
        }

        return res;
    }
};
