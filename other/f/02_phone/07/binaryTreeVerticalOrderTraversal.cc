/*

https://leetcode.com/problems/binary-tree-vertical-order-traversal/

Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).

If two nodes are in the same row and column, the order should be from left to right.

Examples 1:

Input: [3,9,20,null,null,15,7]

   3
  /\
 /  \
 9  20
    /\
   /  \
  15   7

Output:

[
  [9],
  [3,15],
  [20],
  [7]
]
Examples 2:

Input: [3,9,8,4,0,1,7]

     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7

Output:

[
  [4],
  [9],
  [3,0,1],
  [8],
  [7]
]
Examples 3:

Input: [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5)

     3
    /\
   /  \
   9   8
  /\  /\
 /  \/  \
 4  01   7
    /\
   /  \
   5   2

Output:

[
  [4],
  [9,5],
  [3,0,1],
  [8,2],
  [7]
]

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// Solution 1
class Solution {
private:
    struct nodeState {
        TreeNode *node;
        int axis;
        nodeState(TreeNode *n, int a) {
            node = n;
            axis = a;
        }
    };
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        unordered_map<int, vector<int> > m;
        int minAxis, maxAxis;
        vector<vector<int>> res;
        queue<nodeState> q;
        int axis;
        TreeNode *node;

        if(root) {
            q.push({root, 0});
        } else {
            return res;
        }

        minAxis = 0;
        maxAxis = 0;

        while(q.size()) {
            node = q.front().node;
            axis = q.front().axis;
            q.pop();

            minAxis = min(minAxis, axis);
            maxAxis = max(maxAxis, axis);

            m[axis].push_back(node->val);

            if(node->left) {
                q.push({node->left, axis-1});
            }
            if(node->right) {
                q.push({node->right, axis+1});
            }
        }

        for(axis=minAxis; axis<=maxAxis; axis++) {
            res.push_back(m[axis]);
        }

        return res;
    }
};

// Solution 2
class Solution {
private:
    map<int, vector< pair<int, int> > > m;

    void help(TreeNode *node, int axis, int height) {
        if(!node) {
            return;
        }

        help(node->left, axis-1, height+1);
        m[axis].push_back({height, node->val});
        help(node->right, axis+1, height+1);
    }

    struct cmp {
        bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
            if(p1.first == p2.first) {
                return false;
            } else {
                return p1.first<p2.first;
            }
        }
    };

public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        vector<vector<int> > res;
        vector<pair<int, int> > tmp;
        vector<int> r;

        help(root, 0, 0);

        for(auto entry: m) {
            tmp = entry.second;
            sort(tmp.begin(), tmp.end(), cmp());
            r.clear();
            for(auto num: tmp) {
                r.push_back(num.second);
            }
            res.push_back(r);
        }

        return res;
    }
};
