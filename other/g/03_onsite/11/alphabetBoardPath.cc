/*

https://leetcode.com/problems/alphabet-board-path/

On an alphabet board, we start at position (0, 0), corresponding to character board[0][0].

Here, board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"], as shown in the diagram below.

We may make the following moves:

'U' moves our position up one row, if the position exists on the board;
'D' moves our position down one row, if the position exists on the board;
'L' moves our position left one column, if the position exists on the board;
'R' moves our position right one column, if the position exists on the board;
'!' adds the character board[r][c] at our current position (r, c) to the answer.
(Here, the only positions that exist on the board are positions with letters on them.)

Return a sequence of moves that makes our answer equal to target in the minimum number of moves.  You may return any path that does so.

Example 1:

Input: target = "leet"
Output: "DDR!UURRR!!DDD!"

Example 2:

Input: target = "code"
Output: "RR!DDRR!UUL!R!"

Constraints:

1 <= target.length <= 100
target consists only of English lowercase letters.

*/

// Solution 1
class Solution {
public:
    string alphabetBoardPath(string target) {
        string seq;
        int x, y, srcR=0, srcC=0, destR, destC;

        for(auto chr: target) {
            destR = (chr-'a')/5;
            destC = (chr-'a')%5;

            x = destC-srcC;
            y = destR-srcR;

            // first handle less than cases
            if(x<0) {
                seq += string(abs(x), 'L');
            }
            if(y<0) {
                seq += string(abs(y), 'U');
            }
            // then handle greater than cases
            if(x>0) {
                seq += string(x, 'R');
            }
            if(y>0) {
                seq += string(y, 'D');
            }

            srcR = destR;
            srcC = destC;


            seq += '!';
        }

        return seq;
    }
};

// Solution 2
class Solution {
public:
    string alphabetBoardPath(string target) {
        string seq;
        int srcR=0, srcC=0, destR, destC;

        for(auto chr: target) {
            destR = (chr-'a')/5;
            destC = (chr-'a')%5;

            if(destR==5 && destC==0) {
                // end is 'z'
                while(srcC < destC) {
                    seq += 'R';
                    srcC++;
                }

                while(srcC > destC) {
                    seq += 'L';
                    srcC--;
                }

                while(srcR < destR) {
                    seq += 'D';
                    srcR++;
                }

                while(srcR > destR) {
                    seq += 'U';
                    srcR--;
                }
            } else {
                while(srcR < destR) {
                    seq += 'D';
                    srcR++;
                }

                while(srcR > destR) {
                    seq += 'U';
                    srcR--;
                }

                while(srcC < destC) {
                    seq += 'R';
                    srcC++;
                }

                while(srcC > destC) {
                    seq += 'L';
                    srcC--;
                }
            }


            seq += '!';
        }

        return seq;
    }
};
