/*

https://leetcode.com/problems/all-paths-from-source-lead-to-destination/

Given the edges of a directed graph, and two nodes source and destination of this graph, determine whether or not all paths starting from source eventually end at destination, that is:

At least one path exists from the source node to the destination node
If a path exists from the source node to a node with no outgoing edges, then that node is equal to destination.
The number of possible paths from source to destination is a finite number.
Return true if and only if all roads from source lead to destination.

Example 1:

Input: n = 3, edges = [[0,1],[0,2]], source = 0, destination = 2
Output: false
Explanation: It is possible to reach and get stuck on both node 1 and node 2.

Example 2:

Input: n = 4, edges = [[0,1],[0,3],[1,2],[2,1]], source = 0, destination = 3
Output: false
Explanation: We have two possibilities: to end at node 3, or to loop over node 1 and node 2 indefinitely.

Example 3:

Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]], source = 0, destination = 3
Output: true

Example 4:

Input: n = 3, edges = [[0,1],[1,1],[1,2]], source = 0, destination = 2
Output: false
Explanation: All paths from the source node end at the destination node, but there are an infinite number of paths, such as 0-1-2, 0-1-1-2, 0-1-1-1-2, 0-1-1-1-1-2, and so on.

Example 5:

Input: n = 2, edges = [[0,1],[1,1]], source = 0, destination = 1
Output: false
Explanation: There is infinite self-loop at destination node.

*/

class Solution {
public:
    void dfs(unordered_map<int, set<int> > &graph, vector<bool> &visited, int src, int dest, bool &found) {
        if(!found) {
            return;
        }

        if(visited[src] || graph[src].count(src)==1) {
            found = false;
            return;
        }

        if(src == dest) {
            return;
        }

        if(graph[src].size() == 0) {
            found = false;
            return;
        }

        visited[src] = true;
        for(auto node: graph[src]) {
            dfs(graph, visited, node, dest, found);
        }
        visited[src] = false;
    }

    bool leadsToDestination(int n, vector<vector<int>>& edges, int source, int destination) {
        unordered_map<int, set<int> > graph;
        bool found;

        for(auto edge: edges) {
            graph[edge[0]].insert(edge[1]);
        }

        // special case n=1 edges=[] src=0 dest=0
        if(n==1 && edges.size()==0) {
            return true;
        }

        // special case
        // [1] no path from src to dest
        // [2] no outgoing edges from dest
        if(graph[source].size() == 0 || graph[destination].size()) {
            return false;
        }

        for(auto src: graph[source]) {
            vector<bool> visited(n, false);
            found = true;
            dfs(graph, visited, src, destination, found);
            if(!found) {
                return false;
            }
        }

        return true;
    }
};
