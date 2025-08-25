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

class Solution_102 {
public:

    //helper function for traversing a binary tree
    void bfsTraversal(std::vector<std::vector<int>>& ans, TreeNode* node, int level) {
        if (ans.size() == level) {
            std::vector<int> temp;
            ans.push_back(temp);
        }
        ans.at(level).push_back(node->val);
        level++;
        if (node->left) bfsTraversal(ans, node->left, level);
        if (node->right) bfsTraversal(ans, node->right, level);
    }
    
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> ans;
        if (!root) return ans;
        bfsTraversal(ans, root, 0);
        return ans;
    }
};

class Solution_662 {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        std::queue<std::pair<TreeNode*, int>> q;
        int result = 0;

        q.push({root, 1});

        while (!q.empty()) {
            int queueSize = q.size();
            int start = 0, end = 0;
            int addrVal = q.front().second;
            for (int i = 0; i < queueSize; i++) {
                TreeNode* temp = q.front().first;
                int tempVal = q.front().second - addrVal;
                q.pop();

                if (i == 0) start = tempVal;
                if (i == queueSize - 1) end = tempVal;

                if (temp->left) 
                    q.push({temp->left, 2 * tempVal});
                if (temp->right)
                    q.push({temp->right, 2 * tempVal + 1});
            }
            result = std::max(result, end - start + 1);
        }

        return result;
    }
};

int main() {
	//Problem 637: Find the average value of each level in a tree using BFS
	//Problem 100: Check if two trees are identical to each other
    //Problem 98:  Check if a tree is a valid BST (Binary Search Tree)
    //Problem 102: Binary Tree Level Order Traversal
    //Problem 662: Find the maximum width on a Binary Tree
}