/*

https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level X such that the sum of all the values of nodes at level X is maximal.



Example 1:



Input: [1,7,0,7,-8,null,null]
Output: 2
Explanation:
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.


Note:

The number of nodes in the given tree is between 1 and 10^4.
-10^5 <= node.val <= 10^5

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
    int maxLevelSum(TreeNode* root) {
        queue<TreeNode*> q;
        int maxSum = root ? root->val : 0;
        int sum=0, n, level=0, maxLevel=0;
        TreeNode *node;
        if(root) {
            q.push(root);
            maxLevel = 1;
        }
        while(q.size()) {
            n = q.size();
            sum = 0;
            level++;
            while(n--) {
                node = q.front();
                q.pop();
                sum += node->val;
                if(node->left) {
                    q.push(node->left);
                }
                if(node->right) {
                    q.push(node->right);
                }
            }
            if(maxSum < sum) {
                maxSum = sum;
                maxLevel = level;
            }
        }
        return maxLevel;
    }
};
