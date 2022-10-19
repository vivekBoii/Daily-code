#include "bits/stdc++.h"
using namespace std;

// Binary Tree Representation in c++
    struct TreeNode{
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int data) : val(data), left(nullptr), right(nullptr) {}
        TreeNode(int data,TreeNode *left,TreeNode *right) : val(data), left(left), right(right) {}
    };

/* Binary Tree Representation in java 
    public class TreeNode{
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {}
        TreeNode(int data) {
            this.val = data;
        }
        TreeNode(int data,TreeNode left,TreeNode right) {
            this.val = data;
            this.left = left;
            this.right = right;
        }
    }
*/

/* Binary Tree Preorder Traversal */
    class Solution {
    public:
        vector<int> preorder;
        vector<int> preorderTraversal(TreeNode* root) {
            // preorder - root left right
            if(root == NULL) return preorder;
            if(root) preorder.push_back(root->val);
            if(root->left) preorderTraversal(root->left);
            if(root->right) preorderTraversal(root->right);
            return preorder;
        }
    };

