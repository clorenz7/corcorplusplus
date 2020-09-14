/* 
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3

But the following [1,2,2,null,3,null,3] is not:

    1
   / \
  2   2
   \   \
   3    3

 */

/* Strategy:
(1) Breadth First search
(2) Recursive. 
(3) Call is_mirror(left, right)
       left.value == right.value?
       is_mirror(left.left, right.right)?
       is_mirror(left.right, right.left)?
(4) Termination condition is double null ptrs. 
*/

#include<iostream>
#include<vector>

#include "tree_node.h"

using namespace std;

bool isMirror(TreeNode* left, TreeNode* right) {

	if ( left == nullptr ) {
		// Mirrored if both are null
		return right == nullptr;
	}
	else if ( right == nullptr ) {
		// left is not null, right is. 
		return false;
	}

	if ( left->val != right->val ) {
        // If values are not equal, is false
		return false;
	}

	if ( isMirror(left->left, right->right) ) {
		return isMirror(left->right, right->left);
	}
	return false;
}


class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if ( root == nullptr )
            return true;
        return isMirror(root->left, root->right);
    }
};


//---- Testing Code
TreeNode* treeFromArray(vector<int>& vals) {
    TreeNode* root;
    TreeNode* parent;
    TreeNode* child; 
    vector<TreeNode*> TreePointers;

    for (int i=0; i < vals.size(); ++i) {
        child = new TreeNode(vals[i]);
        TreePointers.push_back(child);
        if ( i == 0 ) {
            root = child;
        } else {
            parent = TreePointers[(i-1)/2];
            if ( (i % 2) == 1 ){
                parent->left = child;
            } else {
                parent->right = child;
            }
        }
    }

    return root;
}

int main() {
    TreeNode* root;
    bool answer;
    Solution s = Solution();
    vector<int> vals;
    vals = {1,2,2,3,4,4,3};

    root = treeFromArray(vals);
    answer = s.isSymmetric(root);
    cout << "Expected true, received: " << answer << endl;

    vals = {1,2,2,3,4,4,5};
    root = treeFromArray(vals);
    answer = s.isSymmetric(root);
    cout << "Expected false, received: " << answer << endl;

    return 0;
}