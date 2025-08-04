#include <vector>

class Solution_268 {
public:
    int missingNumber(std::vector<int>& nums) {
        if (nums.size() == 0)
            return 0;

        //find the sum of all numbers in the array
        int actualSum;
        for (int i = 0; i < nums.size(); i++) {
            actualSum += nums[i];
        }

        //we use the formula (n(n+1)) / 2 to find the sum of the first n numbers in the range we're given
        //using this number, we can find the difference between the sums to find which number is missing
        int idealSum = (nums.size() * (nums.size() + 1)) / 2;
        return idealSum - actualSum;
    }
};

int main() {
	//Problem 268: Find the missing number in a sequence of [0, n] distinct numbers in an array
}