#include <vector>
#include <math.h>

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

class Solution_121 {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.size() == 0)
            return 0;

        //initialize variables, one set to the start, one set to our maximum profit
        int minStock = prices[0];
        int maxProf = 0;
        for (int i = 0; i < prices.size(); i++ ) {
            //get the max between the current max profit and the index value - the minimum value
            maxProf = std::max(maxProf, prices[i] - minStock);
            //reset the minimum value based either the index value or whatever the min stock was, whichever is lower
            minStock = std::min(prices[i], minStock);
        }
        return maxProf;
    }
};

class Solution_69 {
public:
    int mySqrt(int x) {
        if (x == 0 || x == 1) return x;

        //implement a basic binary search
        int start = 0, end = x, middle = 0;
        while (start <= end) {
            //to prevent overflow, we need to implement this
            middle = start + (end - start) / 2;
            
            //this is for large numbers that int cannot allocate in C++
            long long square = static_cast<long long>(middle) * middle; 

            if (square > x)
                end = middle - 1;
            else if (square == x)
                return middle;
            else
                start = middle + 1;
        }

        //round when we return the final answer
        return round(end);
    }
};

int main() {
	//Problem 268: Find the missing number in a sequence of [0, n] distinct numbers in an array
    //Problem 69:  Implement the square root function without using the sqrt built in function
}