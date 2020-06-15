/*

https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Example:

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.

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

// https://leetcode.com/problems/serialize-and-deserialize-bst/
// https://leetcode.com/problems/serialize-and-deserialize-n-ary-tree/

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string data;
        queue<TreeNode*> q;
        TreeNode *node;

        q.push(root);

        while(q.size()) {
            node = q.front();
            q.pop();
            if(node) {
                data += to_string(node->val)+",";
                q.push(node->left);
                q.push(node->right);
            } else {
                data += "null,";
            }
        }

        data.erase(data.size()-1);
        return data;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        TreeNode *root = NULL, *node;
        queue<TreeNode*> q;
        stringstream ss(data);
        string token;

        getline(ss, token, ',');

        if(token == "null") {
            return root;
        } else {
            root = new TreeNode(stoi(token));
        }
        q.push(root);

        while(!ss.eof()) {
            node = q.front();
            q.pop();
            getline(ss, token, ',');
            if(token != "null") {
                node->left = new TreeNode(stoi(token));
                q.push(node->left);
            }
            getline(ss, token, ',');
            if(token != "null") {
                node->right = new TreeNode(stoi(token));
                q.push(node->right);
            }
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
