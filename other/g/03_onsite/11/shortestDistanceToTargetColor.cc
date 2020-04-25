/*

https://leetcode.com/problems/shortest-distance-to-target-color/

You are given an array colors, in which there are three colors: 1, 2 and 3.

You are also given some queries. Each query consists of two integers i and c, return the shortest distance between the given index i and the target color c. If there is no solution return -1.



Example 1:

Input: colors = [1,1,2,1,3,2,2,3,3], queries = [[1,3],[2,2],[6,1]]
Output: [3,0,3]
Explanation:
The nearest 3 from index 1 is at index 4 (3 steps away).
The nearest 2 from index 2 is at index 2 itself (0 steps away).
The nearest 1 from index 6 is at index 3 (3 steps away).
Example 2:

Input: colors = [1,2], queries = [[0,3]]
Output: [-1]
Explanation: There is no 3 in the array.


Constraints:

1 <= colors.length <= 5*10^4
1 <= colors[i] <= 3
1 <= queries.length <= 5*10^4
queries[i].length == 2
0 <= queries[i][0] < colors.length
1 <= queries[i][1] <= 3

*/

// Solution 1
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        int dist, n, N=colors.size(), N2=2*N;
        int one=-N2, two=-N2, three=-N2;
        int left, right, index, color;
        vector<int> res;
        vector<vector<int>> lr(3, vector<int>(N, 0)), rl(3, vector<int>(N, 0));


        for(n=0; n<N; n++) {

            switch (colors[n]) {
                case 1:
                    one = n;
                    break;
                case 2:
                    two = n;
                    break;
                case 3:
                    three = n;
                    break;
                default:
                    break;
            }

            lr[0][n] = one;
            lr[1][n] = two;
            lr[2][n] = three;
        }

        one=N2, two=N2, three=N2;
        for(n=N-1; n>=0; n--) {

            switch (colors[n]) {
                case 1:
                    one = n;
                    break;
                case 2:
                    two = n;
                    break;
                case 3:
                    three = n;
                    break;
                default:
                    break;
            }

            rl[0][n] = one;
            rl[1][n] = two;
            rl[2][n] = three;
        }

        for(auto query: queries) {
            index = query[0];
            color = query[1]-1;

            left = lr[color][index];
            right = rl[color][index];

            dist = min(index-left, right-index);cout<<dist<<" ";
            if(dist>N) {
                dist = -1;
            }

            res.push_back(dist);
        }

        return res;
    }
};

// Solution 2
class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        int one=-1, two=-1, three=-1;
        int n, N=colors.size();
        int left, right, index, color;
        vector<int> res;
        vector<vector<int>> lr(3, vector<int>(N, 0)), rl(3, vector<int>(N, 0));


        for(n=0; n<N; n++) {

            switch (colors[n]) {
                case 1:
                    one = n;
                    break;
                case 2:
                    two = n;
                    break;
                case 3:
                    three = n;
                    break;
                default:
                    break;
            }

            lr[0][n] = one;
            lr[1][n] = two;
            lr[2][n] = three;
        }

        one=-1, two=-1, three=-1;
        for(n=N-1; n>=0; n--) {

            switch (colors[n]) {
                case 1:
                    one = n;
                    break;
                case 2:
                    two = n;
                    break;
                case 3:
                    three = n;
                    break;
                default:
                    break;
            }

            rl[0][n] = one;
            rl[1][n] = two;
            rl[2][n] = three;
        }

        for(auto query: queries) {
            index = query[0];
            color = query[1]-1;

            left = lr[color][index];
            right = rl[color][index];

            if(left==-1 && right==-1) {
                res.push_back(-1);
            } else if(left==-1) {
                res.push_back(right-index);
            } else if(right==-1) {
                res.push_back(index-left);
            } else {
                res.push_back(min(index-left, right-index));
            }
        }

        return res;
    }
};

/*

// TLE for Binary & Linear Search

class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        unordered_map<int, vector<int> > cm;
        int color, n, N=colors.size();
        int ans, lb, mid, rb;
        vector<int> target, res;
        bool found;

        for(n=0; n<N; n++) {
            cm[colors[n]].push_back(n);
        }

        for(auto query: queries) {
            n = query[0];
            color = query[1];
            target = cm[color];

            lb = 0;
            rb = target.size()-1;

            if(target.size() == 0) {
                res.push_back(-1);
                continue;
            }
            found = false;

            // look for 'n' in target array
            while(lb<=rb) {
                mid = lb+(rb-lb)/2;
                if(target[mid] == n) {
                    found = true;
                    break;
                }
                else if(n<target[mid]) {
                    rb = mid-1;
                } else {
                    lb = mid+1;
                }
            }

            if(found) {
                res.push_back(0);
            } else {

                ans = INT_MAX;

                if(lb<target.size() && lb>=0) {
                    ans = min(ans, abs(target[lb]-n));
                }
                if(lb+1<target.size()) {
                    ans = min(ans, abs(target[lb+1]-n));
                }
                if(lb-1>=0) {
                    ans = min(ans, abs(target[lb-1]-n));
                }

                res.push_back(ans);
            }

            // linear
            // if(rb == -1) {
            //     res.push_back(-1);
            //     continue;
            // }
            // ans = INT_MAX;
            // while(lb<=rb) {
            //     ans = min(ans, abs(target[lb]-n));
            //     lb++;
            // }
            // res.push_back(ans);
        }
        return res;
    }
};
*/
