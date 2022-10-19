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

/* Binary Tree Inorder Traversal */
    class Solution {
    public:
        vector<int> inorder;
        vector<int> inorderTraversal(TreeNode* root) {
            if(root == nullptr) return inorder;
            if(root->left) inorderTraversal(root->left);
            if(root) inorder.push_back(root->val);
            if(root->right) inorderTraversal(root->right);
            return inorder;
        }
    };

/* Binary Tree postorder Traversal */
    class Solution {
    public:
        vector<int> postorder;
        vector<int> postorderTraversal(TreeNode* root) {
            if(root == nullptr) return postorder;
            if(root->left) postorderTraversal(root->left);
            if(root->right) postorderTraversal(root->right);
            if(root) postorder.push_back(root->val);
            return postorder;
        }
    };

/* Binary Tree Level Order Traversal */
    class Solution {
    public:
        vector<vector<int>> levelOrder(TreeNode* root) {
            queue<TreeNode*> q;
            q.push(root);
            vector<vector<int>> ans;
            
            if(root == nullptr) return ans;
            while(!q.empty()){
                vector<int> temp;
                vector<TreeNode*> v1;
                
                while(!q.empty()){
                    TreeNode* root1 = q.front();    
                    q.pop();
                    temp.push_back(root1->val);
                    if(root1->left) v1.push_back(root1->left);
                    if(root1->right) v1.push_back(root1->right);
                }
                
                ans.push_back(temp);
                for(auto i : v1) q.push(i);
                
            }
            return ans;
        }
    };

