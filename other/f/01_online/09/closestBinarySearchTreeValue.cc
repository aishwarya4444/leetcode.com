/*
https://leetcode.com/problems/closest-binary-search-tree-value/
Given a non-empty binary search tree and a target value, find the value in the BST that is closest to the target.

Note:

Given target value is a floating point.
You are guaranteed to have only one unique value in the BST that is closest to the target.
Example:

Input: root = [4,2,5,1,3], target = 3.714286

    4
   / \
  2   5
 / \
1   3

Output: 4
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
    int closestValue(TreeNode* root, double target) {
        int result=root->val;
        while(root) {
            if(abs(target-root->val)<abs(target-result)) {
                result = root->val;
            }
            if(target <= root->val) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return result;
    }
};
/*
class Solution {
private:
    void solve(TreeNode *root, double &target, int &result) {
        if(!root) {
            return;
        }

        if(abs(root->val-target) < abs(result-target)) {
            result = root->val;
        }

        solve(root->left, target, result);
        solve(root->right, target, result);
    }
public:
    int closestValue(TreeNode* root, double target) {
        int result=root->val;

        solve(root, target, result);

        return result;
    }
};
*/