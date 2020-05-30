/*
https://leetcode.com/problems/find-largest-value-in-each-tree-row/
You need to find the largest value in each row of a binary tree.

Example:
Input:

          1
         / \
        3   2
       / \   \
      5   3   9

Output: [1, 3, 9]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue<TreeNode*> q;
        vector<int> result;
        int maxVal, N;

        if(root) {
            q.push(root);
        }

        while(q.size()) {
            N = q.size();
            maxVal = INT_MIN;
            while(N--) {
                root = q.front();
                q.pop();

                maxVal = max(maxVal, root->val);
                if(root->left) {
                    q.push(root->left);
                }
                if(root->right) {
                    q.push(root->right);
                }
            }
            result.push_back(maxVal);
        }

        return result;
    }
};