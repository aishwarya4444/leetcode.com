/*

https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/

Given a rooted binary tree, return the lowest common ancestor of its deepest leaves.

Recall that:

The node of a binary tree is a leaf if and only if it has no children
The depth of the root of the tree is 0, and if the depth of a node is d, the depth of each of its children is d+1.
The lowest common ancestor of a set S of nodes is the node A with the largest depth such that every node in S is in the subtree with root A.


Example 1:

Input: root = [1,2,3]
Output: [1,2,3]
Explanation:
The deepest leaves are the nodes with values 2 and 3.
The lowest common ancestor of these leaves is the node with value 1.
The answer returned is a TreeNode object (not an array) with serialization "[1,2,3]".
Example 2:

Input: root = [1,2,3,4]
Output: [4]
Example 3:

Input: root = [1,2,3,4,5]
Output: [2,4,5]


Constraints:

The given tree will have between 1 and 1000 nodes.
Each node of the tree will have a distinct value between 1 and 1000.

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

// Solution 1 - 12 ms
class Solution {
private:
    int maxH;
    int help(TreeNode *node, int h, TreeNode *&lca) {
        maxH = max(maxH, h);
        if(!node) {
            return h;
        }
        int lh = help(node->left, h+1, lca);
        int rh = help(node->right, h+1, lca);

        if(lh == rh && lh == maxH) {
            lca = node;
        }

        return max(lh, rh);
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        TreeNode *lca = NULL;
        maxH = 0;
        help(root, 0, lca);
        return lca;
    }
};

// Solution 2 - 24 ms
class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        if(!root)
            return root;
        int l = get_dep(root->left);
        int r = get_dep(root->right);
        if(l==r)
            return root;
        else
            return l>r ? lcaDeepestLeaves(root->left) : lcaDeepestLeaves(root->right);
    }

    int get_dep(TreeNode* root) {
        if(!root)
            return 0;
        int a = get_dep(root->left);
        int b = get_dep(root->right);
        return max(a, b)+1;

    }
};

// Solution 3 - 24 ms
class Solution {
public:
    int maxHeight(TreeNode *node) {
        if(!node) {
            return 0;
        }
        return 1+max(maxHeight(node->left), maxHeight(node->right));
    }

    void populate(TreeNode *root, unordered_map<TreeNode*, int> &occur, vector<TreeNode*> &tmp, vector<TreeNode*> &bkp, int h, int d) {
        if(!root) {
            return;
        }
        h++;
        tmp.push_back(root);
        if(h==d) {
            for(auto node: tmp) {
                occur[node]++;
            }
            if(bkp.size()==0) {
                for(auto node: tmp) {
                    bkp.push_back(node);
                }
            }
        }
        populate(root->left, occur, tmp, bkp, h, d);
        populate(root->right, occur, tmp, bkp, h, d);
        tmp.pop_back();
    }

    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        int d = maxHeight(root), h=0, leavesAt_d=0;
        unordered_map<TreeNode*, int> occur;
        vector<TreeNode*> tmp, bkp;
        TreeNode *res;

        populate(root, occur, tmp, bkp, h, d);

        leavesAt_d = occur[root];

        for(auto node: bkp) {
            if(occur[node] == leavesAt_d) {
                res = node;
            }
        }

        return res;
    }
};
