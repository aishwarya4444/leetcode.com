/*

https://leetcode.com/problems/android-unlock-patterns/

Given an Android 3x3 key lock screen and two integers m and n, where 1 ≤ m ≤ n ≤ 9, count the total number of unlock patterns of the Android lock screen, which consist of minimum of m keys and maximum n keys.



Rules for a valid pattern:

Each pattern must connect at least m keys and at most n keys.
All the keys must be distinct.
If the line connecting two consecutive keys in the pattern passes through any other keys, the other keys must have previously selected in the pattern. No jumps through non selected key is allowed.
The order of keys used matters.





Explanation:

| 1 | 2 | 3 |
| 4 | 5 | 6 |
| 7 | 8 | 9 |
Invalid move: 4 - 1 - 3 - 6
Line 1 - 3 passes through key 2 which had not been selected in the pattern.

Invalid move: 4 - 1 - 9 - 2
Line 1 - 9 passes through key 5 which had not been selected in the pattern.

Valid move: 2 - 4 - 1 - 3 - 6
Line 1 - 3 is valid because it passes through key 2, which had been selected in the pattern

Valid move: 6 - 5 - 4 - 1 - 9 - 2
Line 1 - 9 is valid because it passes through key 5, which had been selected in the pattern.



Example:

Input: m = 1, n = 1
Output: 9

*/

/*

https://leetcode.com/problems/android-unlock-patterns/discuss/82483/Sharing-my-bitmask-dynamic-programming-solution-(4ms)

https://www.geeksforgeeks.org/number-of-ways-to-make-mobile-lock-pattern/

*/

class Solution {
private:
    // declaration can be done here
    // but size cannot be mentioned here
    vector<vector<vector<int>>> dp;
public:
    int ways(vector<vector<int>> &kp, int m, int start, int state) {
        if(m == 0) {
            return 1;
        }

        if(dp[m][start][state] != -1) {
            return dp[m][start][state];
        }

        int len = 0, kpState;
        for(int i=1; i<=9; i++) {
            kpState = state | (1<<i);
            if(state != kpState) {
                if(kp[i][start]==0 || (state & (1<<kp[i][start]))) {
                    len += ways(kp, m-1, i, kpState);
                }
            }
        }
        dp[m][start][state] = len;
        return len;
    }

    int numberOfPatterns(int m, int n) {
        vector<vector<int>> kp(10, vector<int>(10, 0));
        vector<bool> visited(10, false);
        int count = 0;

        // init keypad
        // kp[i][j] = kp[j][i] = "number" between "i" and "j" on keypad
        // if this "number" has been visited we can cross this "number" else we cannot cross
        kp[1][3] = kp[3][1] = 2;
        kp[1][7] = kp[7][1] = 4;
        kp[3][9] = kp[9][3] = 6;
        kp[9][7] = kp[7][9] = 8;
        kp[2][8] = kp[8][2] = 5;
        kp[4][6] = kp[6][4] = 5;
        kp[1][9] = kp[9][1] = 5;
        kp[3][7] = kp[7][3] = 5;

        if(m>n) {
            swap(m, n);
        }

        // dp[length][keyNum][state]
        dp.resize(n+1);
        // gives error
        // for(auto twoDim: dp) {
        //     twoDim.resize(10);
        //     for(auto oneDim: twoDim) {
        //         oneDim.resize((1<<10), -1);
        //     }
        // }
        for (int i=0; i<=n; i++) {
            dp[i].resize(10);
            for (int j=0; j<10; j++) {
                dp[i][j].resize((1<<10), -1);
            }
        }

        while(m<=n) {
            count += ways(kp, m, 0, 0);
            m++;
        }

        return count;
    }
};

/*

// DFS bactracking solution .. slow

class Solution {
public:
    int ways(vector<vector<int>> &kp, vector<bool> visited, int start, int m) {
        if(m == 1) {
            return 1;
        }

        if(m < 1) {
            return 0;
        }

        int len = 0;
        visited[start] = true;
        for(int i=1; i<=9; i++) {
            if(!visited[i]) {
                if(kp[i][start]==0 || visited[kp[i][start]]) {
                    len += ways(kp, visited, i, m-1);
                }
            }
        }
        visited[start] = false;
        return len;
    }

    int numberOfPatterns(int m, int n) {
        vector<vector<int>> kp(10, vector<int>(10, 0));
        vector<bool> visited(10, false);
        int count = 0;

        // init keypad
        // kp[i][j] = kp[j][i] = "number" between "i" and "j" on keypad
        // if this "number" has been visited we can cross this "number" else we cannot cross
        kp[1][3] = kp[3][1] = 2;
        kp[1][7] = kp[7][1] = 4;
        kp[3][9] = kp[9][3] = 6;
        kp[9][7] = kp[7][9] = 8;
        kp[2][8] = kp[8][2] = 5;
        kp[4][6] = kp[6][4] = 5;
        kp[1][9] = kp[9][1] = 5;
        kp[3][7] = kp[7][3] = 5;

        if(m>n) {
            swap(m, n);
        }
        while(m<=n) {
            // start from 1 is similar to start from 1, 3, 7, 9
            count += 4*ways(kp, visited, 1, m);
            // start from 2 is similar to start from 2, 4, 6, 8
            count += 4*ways(kp, visited, 2, m);
            // 5 is at center and no other digit is symmetric for this case
            count += ways(kp, visited, 5, m);
            m++;
        }

        return count;
    }
};
*/
