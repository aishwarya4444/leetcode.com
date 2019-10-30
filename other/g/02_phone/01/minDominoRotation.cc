/*

https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/
In a row of dominoes, A[i] and B[i] represent the top and bottom halves of the i-th domino.  (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the i-th domino, so that A[i] and B[i] swap values.

Return the minimum number of rotations so that all the values in A are the same, or all the values in B are the same.

If it cannot be done, return -1.



Example 1:



Input: A = [2,1,2,4,2,2], B = [5,2,6,2,3,2]
Output: 2
Explanation:
The first figure represents the dominoes as given by A and B: before we do any rotations.
If we rotate the second and fourth dominoes, we can make every value in the top row equal to 2, as indicated by the second figure.
Example 2:

Input: A = [3,5,1,2,3], B = [3,6,3,3,4]
Output: -1
Explanation:
In this case, it is not possible to rotate the dominoes to make one row of values equal.


Note:

1 <= A[i], B[i] <= 6
2 <= A.length == B.length <= 20000

*/

class Solution {
public:
    bool isPossible(int val, vector<int>& A, vector<int>& B) {
        int n, N=A.size();
        for(n=0; n<N; n++) {
            if(A[n]!=val && B[n]!=val) {
                return false;
            }
        }
        return true;
    }
    int minDominoRotations(vector<int>& A, vector<int>& B) {
        bool useA=isPossible(A[0], A, B), useB=isPossible(B[0], A, B);
        int N=A.size(), countA=N, countB=N, cA=N, cB=N;

        if(!useA && !useB) {
            return -1;
        }

        if(useA) {
            countA = 0;
            cA=0;
            for(auto num: A) {
                if(num == A[0]) {
                    countA++;
                }
            }


            for(auto num: B) {
                if(num == A[0]) {
                    cA++;
                }
            }

            countA = min(countA, N-countA);
            cA = min(cA, N-cA);
            countA = min(countA, cA);
        }

        if(useB) {
            countB = 0;
            cB = 0;
            for(auto num: B) {
                if(num == B[0]) {
                    countB++;
                }
            }

            for(auto num: A) {
                if(num == B[0]) {
                    cB++;
                }
            }
            countB = min(countB, N-countB);
            cB = min(cB, N-cB);
            countB = min(countB, cB);
        }

        return min(countA, countB);
    }
};
