/*

https://leetcode.com/problems/flower-planting-with-no-adjacent/

You have N gardens, labelled 1 to N.  In each garden, you want to plant one of 4 types of flowers.

paths[i] = [x, y] describes the existence of a bidirectional path from garden x to garden y.

Also, there is no garden that has more than 3 paths coming into or leaving it.

Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.

Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)-th garden.  The flower types are denoted 1, 2, 3, or 4.  It is guaranteed an answer exists.



Example 1:

Input: N = 3, paths = [[1,2],[2,3],[3,1]]
Output: [1,2,3]
Example 2:

Input: N = 4, paths = [[1,2],[3,4]]
Output: [1,2,1,2]
Example 3:

Input: N = 4, paths = [[1,2],[2,3],[3,4],[4,1],[1,3],[2,4]]
Output: [1,2,3,4]

*/

class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        int n, color, parent, child;
        vector<int> result(N, 0), children;

        unordered_map<int, vector<int>> graph;
        for(auto path: paths) {
            parent = path[0]-1;
            child = path[1]-1;
            graph[parent].push_back(child);
            graph[child].push_back(parent);
        }

        for(n=0; n<N; n++) {
            children = graph[n];
            unordered_set<int> filledColors;
            for(auto child: children) {
                filledColors.insert(result[child]);
            }
            for(color=1; color<=4; color++) {
                if(filledColors.count(color)) {
                    continue;
                }
                result[n] = color;
                break;
            }
        }
        return result;
    }
};