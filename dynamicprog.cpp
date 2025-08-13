#include <vector>
#include <math.h>


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

int main() {
	//Problem 322: Return minumum number of coins required from a coin denomination list to reach an amount
}