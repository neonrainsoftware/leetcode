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

int main() {
	//Problem 22: Generate a number of parenthesis based on any number n
}