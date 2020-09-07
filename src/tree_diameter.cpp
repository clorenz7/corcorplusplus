/*
Given a binary tree, you need to compute the length of the diameter of the tree.
The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root.

Example:
Given a binary tree
          1
         / \
        2   3
       / \
      4   5
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.

Basic strategy:
(1) Calculate the longest path on the left and the right
(2) The diameter going through any node is the sum of the two
(3) Pick the max diameter - can I do this in place?

*/

#include<iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


int longestPath(TreeNode* root, int* maxDiameter) {

    if (root == nullptr ) {
        return -1;
    }

    int left_path, right_path, diameter;
    left_path = longestPath(root->left, maxDiameter)+1;
    right_path = longestPath(root->right, maxDiameter)+1;
    diameter = left_path + right_path;

    if (diameter > *maxDiameter) {
        *maxDiameter = diameter;
    }

    if (left_path >= right_path)
        return left_path;
    else
        return right_path;
}


class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int maxDiameter = 0;
        longestPath(root, &maxDiameter);

        return maxDiameter;
    }
};

int main() {

    Solution s = Solution();

    TreeNode* three = new TreeNode(3);
    TreeNode* four = new TreeNode(4);
    TreeNode* five = new TreeNode(5);

    TreeNode* two = new TreeNode(2, four, five);
    TreeNode* root = new TreeNode(1, two, three);

    int D;
    D = s.diameterOfBinaryTree(root);

    cout << "Expect 3, got: " << D << endl;

    TreeNode* six = new TreeNode(6);
    TreeNode* seven = new TreeNode(7);
    TreeNode* eight = new TreeNode(8);
    TreeNode* nine = new TreeNode(9);

    four->right = six;
    five->left = seven;
    seven->right = eight;
    eight->left = nine;

    D = s.diameterOfBinaryTree(root);

    cout << "Expect 6, got: " << D << endl;

    return 0;
}

