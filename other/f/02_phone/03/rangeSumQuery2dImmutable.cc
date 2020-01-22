/*

https://leetcode.com/problems/range-sum-query-2d-immutable/

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
Note:
You may assume that the matrix does not change.
There are many calls to sumRegion function.
You may assume that row1 ≤ row2 and col1 ≤ col2.

*/

class NumMatrix {
private:
    vector<vector<int>> dp;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int r, c, R = matrix.size(), C = R ? matrix[0].size(): 0;
        dp.resize(R+1, vector<int>(C+1, 0));

        for(r=1; r<=R; r++) {
            for(c=1; c<=C; c++) {
                dp[r][c] = dp[r][c-1]+dp[r-1][c]+matrix[r-1][c-1]-dp[r-1][c-1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2+1][col2+1]-dp[row2+1][col1]-dp[row1][col2+1]+dp[row1][col1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

 /*
 class NumMatrix {
 private:
     vector<vector<int> > m;
 public:
     NumMatrix(vector<vector<int>>& matrix) {
         int r, c, R=matrix.size(), C=R?matrix[0].size():R;

         m = matrix;

         for(c=0; c<C; c++) {
             for(r=1; r<R; r++) {
                 m[r][c] += m[r-1][c];
             }
         }

         for(r=0; r<R; r++) {
             for(c=1; c<C; c++) {
                 m[r][c] += m[r][c-1];
             }
         }
     }

     int sumRegion(int row1, int col1, int row2, int col2) {
         if(row1>0 && col1>0) {
             return m[row2][col2]-m[row1-1][col2]-m[row2][col1-1]+m[row1-1][col1-1];
         } else if(row1>0) {
             return m[row2][col2]-m[row1-1][col2];
         } else if(col1>0) {
             return m[row2][col2]-m[row2][col1-1];
         } else {
             return m[row2][col2];
         }
     }
 };
 */
