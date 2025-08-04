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
                if (temp->left != nullptr) treeQueue.push(temp->left);
                if (temp->right != nullptr) treeQueue.push(temp->right);
				//add the sum to a temporary variable that we then push the average of to the answer array
                res += temp->val;
            }
            ans.push_back(res / queueSize);
        }
        return ans;
    }   
};

int main() {
	//Problem 637: Find the average value of each level in a tree using BFS
}