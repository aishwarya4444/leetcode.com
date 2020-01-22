/*

https://leetcode.com/problems/range-sum-of-bst/

Given the root node of a binary search tree, return the sum of values of all nodes with value between L and R (inclusive).

The binary search tree is guaranteed to have unique values.



Example 1:

Input: root = [10,5,15,3,7,null,18], L = 7, R = 15
Output: 32
Example 2:

Input: root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
Output: 23


Note:

The number of nodes in the tree is at most 10000.
The final answer is guaranteed to be less than 2^31.

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
private:
    // void help(TreeNode* root, int L, int R, int &sum) {
    //     if(!root) {
    //         return;
    //     }
    //     help(root->left, L, R, sum);
    //     if(root->val >= L && root->val <= R) {
    //         sum += root->val;
    //     }
    //     help(root->right, L, R, sum);
    // }

    void help(TreeNode* root, int L, int R, int &sum) {
        if(!root) {
            return;
        }
        if(root->val > R) {
            help(root->left, L, R, sum);
        } else if(root->val < L) {
            help(root->right, L, R, sum);
        } else {
            help(root->left, L, R, sum);
            sum += root->val;
            help(root->right, L, R, sum);
        }
    }

public:
    int rangeSumBST(TreeNode* root, int L, int R) {
        int sum=0;
        help(root, L, R, sum);
        return sum;
    }
};
