#include <vector>
#include <math.h>
#include <string>

class Solution_322 {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        if (coins.size() == 0) return -1;
		//technically, making a helper function is not necessary, but is good if we want to change the
		//list for whatever reason, in which case we could turn this into a recursive algorithm
        return checkCoins(coins, amount);
    }

    int checkCoins(std::vector<int>& coins, int amt) {
		//create a sample list thats the same size as the amount we're looking for, filled with the same values.
		//we're effectively keeping track of the amount of each value for each coin in the list, subtracting from
		//each entry each time
		//amount + 1 because we need to take 0 into account
        std::vector<int> res(amt + 1, amt + 1);
		//0 coins are needed to make the amount of 0
        res[0] = 0;
        for (int i = 1; i <= amt; i++) {
			//we don't care about the index for looking at each coin value, so we can use a for each loop here
            for (auto coin : coins) {
				//subtract coin value for each i that we're looking at and if it fits, update the value with that
				//number
                if (i - coin >= 0)
                    res[i] = std::min(res[i], res[i - coin] + 1);
            }
        }

        return res[amt] == amt + 1 ? -1 : res[amt];
    }
};

class Solution_139 {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        if (s.size() == 0) return false;

        //this is a vague interpretation of dynamic programming, but it can be classified as such
        //create a vector thats the same size as your word list and fill it with false
        //we'll use the bool to return the final result
        std::vector<bool> dp(wordDict.size() + 1, false);
        //the first value is always true
        dp[0] = true;

        for (int i = 1; i <= s.size(); i++) {
            
            //we don't care about the index, so we can just use a for each loop
            for (auto word : wordDict) {
                
                //find the start index 
                int start = i - word.size();

                //if the word exists and the index we're currently looking at is set to true and the substring
                //of the word within the string s fits, then we found a neat fit, set the current i value in the
                //dp array to true and move on to the next word
                if (start >= 0 && dp[start] && s.substr(start, word.size()) == word) {
                    dp[i] = true;
                    break;
                }
            }
        }

        //return the last element of the array because that will tell us if all the words would fit within
        //the string s
        return dp[s.size()];
    }
};

class Solution_70 {
public:

    int solveStairs(int n, std::vector<int>& tempVec) {
        if (n == 0 || n == 1) return 1;
        if (tempVec[n] != -1) return tempVec[n]; 
        tempVec[n] = (solveStairs(n - 1, tempVec) + solveStairs(n - 2, tempVec));
        return tempVec[n];
    }

    int climbStairs(int n) {
        if (n <= 0) return 0;
        std::vector<int> tempVec(n+1, -1);
        return solveStairs(n, tempVec);
    }
};

int main() {
	//Problem 322: Return minumum number of coins required from a coin denomination list to reach an amount
    //Problem 139: Return if an string can be split up cleanly based on the words from a given word list
    //Problem 70:  Return the number of distinct ways to climb a stairs list
}