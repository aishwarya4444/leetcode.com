/*

https://leetcode.com/problems/evaluate-division/

Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].


The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.

*/

/*
https://leetcode.com/problems/evaluate-division/discuss/354643/c%2B%2B-union-find-update-only-one-node-every-union-operation-with-explanation

https://leetcode.com/problems/evaluate-division/discuss/88170/0ms-C%2B%2B-Union-Find-Solution-EASY-to-UNDERSTAND
*/
class Solution {
private:
    struct Node {
        string parent;
        double value;
        Node(string par, double val) {
            parent = par;
            value = val;
        }
    };

    unordered_map<string, Node*> p;

    string _find(string n, double &val) {
        while(p[n]->parent != n) {
            val = val*p[n]->value;
            n = p[n]->parent;
        }
        return n;
    }

    void _union(string n1, string n2, double val) {
        double v1=1.0, v2=1.0;
        string p1 = _find(n1, v1), p2 = _find(n2, v2);

        if(p1 != p2) {
            p[p1]->parent = p2;
            p[p1]->value = val*v2/v1;;
        }
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int index=0;
        double v1, v2;
        string n1, n2, p1, p2;
        vector<double> res;

        for(auto eqn: equations) {
            if(p.count(eqn[0]) == 0) {
                p[eqn[0]] = new Node(eqn[0], 1.0);
            }
            if(p.count(eqn[1]) == 0) {
                p[eqn[1]] = new Node(eqn[1], 1.0);
            }
            _union(eqn[0], eqn[1], values[index]);
            index++;
        }

        for(auto query: queries) {
            n1 = query[0];
            n2 = query[1];

            if(p.count(n1)==0 || p.count(n2)==0) {
                res.push_back(-1);
                continue;
            }

            if(n1 == n2) {
                res.push_back(1);
                continue;
            }

            v1 = 1.0;
            v2 = 1.0;

            p1 = _find(n1, v1);
            p2 = _find(n2, v2);

            if(p1 != p2) {
                res.push_back(-1);
                continue;
            }
            res.push_back(v1/v2);
        }

        return res;
    }
};
