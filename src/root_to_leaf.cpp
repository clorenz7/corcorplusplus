/*
Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

Note: A leaf is a node with no children.

Example:

Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
Example 2:

Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.


// Strategy:
(1) Do a BFS - a queue (vector) of pairs: (node, current sum)
(2) Keep a running total of the sum as you go. Multiply it by 10 each time you go to a new level
(3) When you reach a leaf, you add it to the total.

*/

#include<iostream>
#include<queue>
#include<utility>
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

class Solution {
public:
    int sumNumbers(TreeNode* root) {

        if (root == nullptr)
            return 0;

        int sum = 0;
        pair<TreeNode*, int> node_pair;
        TreeNode* leftNode;
        TreeNode* rightNode;
        int runningSum;

        queue<pair<TreeNode*, int>> q;
        q.push(pair<TreeNode*, int>(root, 0));

        while (!q.empty()) {
            node_pair = q.front();

            leftNode = node_pair.first->left;
            rightNode = node_pair.first->right;
            runningSum = node_pair.second + node_pair.first->val;

            if (leftNode == nullptr && rightNode == nullptr) {
                sum += runningSum;
            } else {
                if (leftNode != nullptr) {
                    q.push(pair<TreeNode*, int>(leftNode, 10*runningSum));
                }

                if (rightNode != nullptr) {
                    q.push(pair<TreeNode*, int>(rightNode, 10*runningSum));
                }
            }

            q.pop();
        }

        return sum;
    }
};


int main () {
    Solution s = Solution();
    int sum;


    TreeNode two = TreeNode(2);
    TreeNode three = TreeNode(3);
    TreeNode root = TreeNode(1, &two, &three);

    sum = s.sumNumbers(&root);

    cout << "Expected 25, got: " << sum << endl;

    TreeNode one = TreeNode(1);
    TreeNode five = TreeNode(5);
    TreeNode zero = TreeNode(0);

    TreeNode nine = TreeNode(9, &five, &one);
    TreeNode four = TreeNode(4, &nine, &zero);

    sum = s.sumNumbers(&four);

    cout << "Expected 1026, got: " << sum << endl;


    sum = s.sumNumbers(&five);
    cout << "Expected 5, got: " << sum << endl;

    return 0;
}