#include <vector>
#include <string>

class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        if (n <= 0) return std::vector<std::string>();
        std::vector<std::string> result;
        dfs(0, 0, "", n, result);
        return result;
    }

    //depth-first search algorithm using recursive function calls
    void dfs(int openParen, int closedParen, std::string s, int n, std::vector<std::string>& result) {
        //if we reached the maximum number of parenthesis and ran out of extras
        //push the string into the vector passed by reference and exit out early
        if (openParen == closedParen && openParen + closedParen == n * 2) {
            result.push_back(s);
            return;
        } 
        //if the number of open parenthesis is less than n, recursively call dfs again,
        //incrementing the first number and adding a ( to the string
        if (openParen < n)
            dfs(openParen + 1, closedParen, s + "(", n, result);
        //if the number of closed parenthesis is less than n, recursively call dfs again,
        //incrementing the second number and adding a ) to the string
        if (closedParen < openParen)
            dfs(openParen, closedParen + 1, s + ")", n, result);

        //in all other cases, do nothing
    }
};

class Solution {
public:
    int findTargetSumWays(std::vector<int>& nums, int target) {
        if (nums.size() == 0) return 0; 
        //never modify the incoming data unless explictly stated otherwise
        std::vector<int> result = nums;
        return sumHelper(result, target, 0, 0);
    }

    //we use a recursive solution when we need to make permutations like this problem
    int sumHelper(std::vector<int>& vec, int target, int index, int sum) {
        //we return early if we found that the index is greater than our size of the array, because 
        //we've reached a point where subtraction and/or addition is no longer possible
        if (vec.size() <= index)
            return 1 ? sum == target : 0;
        
        //we're adding or subtracting the number based on which number in the array that we're
        //currently looking at
        int subtract = sumHelper(vec, target, index + 1, sum - vec[index]);
        int add = sumHelper(vec, target, index + 1, sum + vec[index]);

        //return the result if we don't return early
        return subtract + add; 
    }
};

int main() {
	//Problem 22: Generate a number of parenthesis based on any number n
	//Problem 494: Return all possible +/- expressions given a vector and a target number
}