/*

https://leetcode.com/problems/delete-nodes-and-return-forest/

Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest.  You may return the result in any order.



Example 1:



Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]


Constraints:

The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.

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
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> result;
        pair<TreeNode*, TreeNode*> nodePair;
        TreeNode *parent, *curr;
        queue<pair<TreeNode*, TreeNode*> > q;
        bool deleteLeftChild, deleteRightChild, deleteCurr;

        if(root) {
            q.push({NULL, root});
        }

        while(q.size()) {
            nodePair = q.front();
            q.pop();

            parent = nodePair.first;
            curr = nodePair.second;

            deleteCurr = find(to_delete.begin(), to_delete.end(), curr->val) != to_delete.end();

            if(!parent && !deleteCurr) {
                result.push_back(curr);
            }

            if(deleteCurr && parent && parent->left==curr) {
                parent->left = NULL;
            }

            if(deleteCurr && parent && parent->right==curr) {
                parent->right = NULL;
            }

            if(curr->left) {
                if(deleteCurr) {
                    q.push({NULL, curr->left});
                } else {
                    q.push({curr, curr->left});
                }
            }
            if(curr->right) {
                if(deleteCurr) {
                    q.push({NULL, curr->right});
                } else {
                    q.push({curr, curr->right});
                }
            }
        }

        return result;
    }
};
