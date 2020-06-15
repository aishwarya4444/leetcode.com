/*

https://leetcode.com/problems/is-graph-bipartite/

Given an undirected graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.

Example 1:
Input: [[1,3], [0,2], [1,3], [0,2]]
Output: true
Explanation:
The graph looks like this:
0----1
|    |
|    |
3----2
We can divide the vertices into two groups: {0, 2} and {1, 3}.
Example 2:
Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
Output: false
Explanation:
The graph looks like this:
0----1
| \  |
|  \ |
3----2
We cannot find a way to divide the set of nodes into two independent subsets.


Note:

graph will have length in range [1, 100].
graph[i] will contain integers in range [0, graph.length - 1].
graph[i] will not contain i or duplicate values.
The graph is undirected: if any element j is in graph[i], then i will be in graph[j].

*/

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // RED = 1
        // BLUE = 2
        // No Colour = 0
        int node, parent, colour, P=graph.size();
        unordered_map<int, int> nodeColour;
        vector<bool> visited(P, false);
        queue<int> q;

        for(node=0; node<P; node++) {
            if(graph[node].size() == 0) {
                continue;
            }

            if(nodeColour[node]) {
                continue;
            }

            // assign RED to node with no colour
            nodeColour[node] = 1;
            q.push(node);

            while(q.size()) {
                parent = q.front();
                colour = nodeColour[parent];
                q.pop();

                if(visited[parent]) {
                    continue;
                }
                visited[parent] = true;

                for(auto child: graph[parent]) {
                    if(visited[child]) {
                        continue;
                    }

                    // if parent is of RED colour
                    if(colour == 1) {
                        // child sholud be BLUE
                        if(nodeColour[child] == 1) {
                            return false;
                        }
                        nodeColour[child] = 2;
                        q.push(child);
                    }
                    // if parent is of BLUE colour
                    else {
                        // child should be RED
                        if(nodeColour[child] == 2) {
                            return false;
                        }
                        nodeColour[child] = 1;
                        q.push(child);
                    }
                }
            }
        }

        return true;
    }
};
