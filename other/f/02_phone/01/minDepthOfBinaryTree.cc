/*

https://leetcode.com/problems/minimum-depth-of-binary-tree/

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.

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
class Solution {
public:
    void help(TreeNode *root, int height, int &minH) {
        if(!root) return;
        if(!root->left && !root->right) {
            minH = min(minH, height+1);
        }
        help(root->left, height+1, minH);
        help(root->right, height+1, minH);
    }
    int minDepth(TreeNode* root) {
        int height=0, minH=INT_MAX;
        help(root, height, minH);
        return minH==INT_MAX ? 0 : minH;
    }
};

/*
class Solution {
public:
    int minDepth(TreeNode* root) {
        queue<TreeNode*> q;
        int N, level=0;

        if(root) {
            q.push(root);
        }

        while(q.size()) {
            N = q.size();
            level++;
            while(N--) {
                root = q.front();
                q.pop();
                if(!root->left && !root->right) {
                    return level;
                }
                if(root->left) {
                    q.push(root->left);
                }
                if(root->right) {
                    q.push(root->right);
                }
            }
        }

        return level;
    }
};
*/
