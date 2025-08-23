#include <vector>
#include <queue>

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 

class Solution_637 {
public:
    std::vector<double> averageOfLevels(TreeNode* root) {
		//this is a classic BFS problem
        std::vector<double> ans;
		//we need a queue to keep track of the nodes we visited
        std::queue<TreeNode*> treeQueue;

		//push the first node in the tree to start
        treeQueue.push(root);
		//while the queue is not empty
        while (!treeQueue.empty()) {
			//we get its size to use for knowing the amount of nodes in that level
            int queueSize = treeQueue.size();
            double res = 0;
            TreeNode* temp;
            for (int i = 0; i < queueSize; i++) {
				//take the first node in the queue
                temp = treeQueue.front(); 
                treeQueue.pop();
				//add the left and right nodes to the queue to continue through to the next level
                if (!temp->left) treeQueue.push(temp->left);
                if (!temp->right) treeQueue.push(temp->right);
				//add the sum to a temporary variable that we then push the average of to the answer array
                res += temp->val;
            }
            ans.push_back(res / queueSize);
        }
        return ans;
    }   
};

class Solution_100 {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
		//another classic BFS search
		//are no trees there? then its true
        if (!p && !q) return true;
        return checkTree(p, q);
    }

    bool checkTree(TreeNode* nodeOne, TreeNode* nodeTwo) {
		//if the nodes on this level are not there, then its true
        if (!nodeOne && !nodeTwo) return true;
		//if one exists but not hte other, then its false
        if (!nodeOne || !nodeTwo) return false;
		//we check the boolean value of what we return by recursively calling this function on the left and right nodes of each branching path
        return (nodeOne->val == nodeTwo->val && (checkTree(nodeOne->left, nodeTwo->left) && checkTree(nodeOne->right, nodeTwo->right)));
    }
};

class Solution_98 {
public:
    bool isValidBST(TreeNode* root) {

        //a valid BST would be one who's node values are never greater than or equal to the root node values
        //the amount of leaf nodes or how those are balanced does not matter

        return validateTree(root, nullptr, nullptr);
    }
    
    //helper function to help us determine the validity of a BST
    bool validateTree(TreeNode* root, TreeNode* left, TreeNode* right) {
        //if the root isn't there, then we return true because we've reached a leaf
        if (!root) return true;
        
        //if the leaf nodes exist, but the left value or the right value is greater than
        //or equal to the root value, return false immediately, the rest of the evaluation
        //doesn't matter by that point because you know it's not a valid BST
        if ((left && left->val >= root->val) || (right && root->val >= right->val))
            return false;   
        
        //continue iterating, passing in the left or right as the root nodes as well as everything
        //else that's required
        return validateTree(root->left, left, root) && validateTree(root->right, root, right);
    }
};

int main() {
	//Problem 637: Find the average value of each level in a tree using BFS
	//Problem 100: Check if two trees are identical to each other
    //Problem 98:  Check if a tree is a valid BST (Binary Search Tree)
}