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
        vector<TreeNode*> res;
        queue<pair<TreeNode*, TreeNode*> > q;
        int n, l, m, r;
        bool shouldDelete;
        TreeNode *empty=NULL, *prev=NULL, *curr=root;
        pair<TreeNode*, TreeNode*> node;
        q.push(make_pair(prev, curr));
        sort(to_delete.begin(), to_delete.end());
        while(q.size()) {
            n = q.size();
            while(n--) {
                node = q.front();
                q.pop();
                prev = node.first;
                curr = node.second;

                // binary search to check node has to be deleted
                shouldDelete = false;
                l = 0;
                r = to_delete.size()-1;
                while(l<=r) {
                    m = l+(r-l)/2;
                    if(to_delete[m]==curr->val) {
                        shouldDelete = true;
                        break;
                    } else if(to_delete[m]>curr->val) {
                        r = m-1;
                    } else {
                        l = m+1;
                    }
                }
                // shouldDelete = find(to_delete.begin(), to_delete.end(), curr->val)!=to_delete.end();

                if(shouldDelete) {
                    if(curr->left) q.push(make_pair(empty, curr->left));
                    if(curr->right) q.push(make_pair(empty, curr->right));
                    if(prev) {
                        if(prev->left == curr) prev->left = NULL;
                        else prev->right = NULL;
                    }
                    // if(curr!=root) delete curr;
                } else {
                    if(curr->left) q.push(make_pair(curr, curr->left));
                    if(curr->right) q.push(make_pair(curr, curr->right));
                    if(!prev) res.push_back(curr);
                }
            }
        }
        return res;
    }
};
