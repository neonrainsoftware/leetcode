#include <vector>
#include <math.h>
#include <unordered_map>
#include <map>
#include <algorithm>

class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        if (nums.size() == 0) return nums;
        int size = nums.size();

        //the concept here is to split the array into two distinct parts, one with the higher end and the other with the lower
        //each named prefix and suffix respectively, and each padded out with the size of the nums array
        std::vector<int> ans(size);
        std::vector<int> prefix(size);
        std::vector<int> suffix(size);
        //we preset the prefix and suffix with 1 to help start the loops
        prefix[0] = 1;
        suffix[size-1] = 1;
        
        //looping through the prefix to appropriately find the product for each of the array elements in the prefix
        for (int i = 1; i < size; i++) 
            prefix[i] = nums[i-1] * prefix[i-1];

        //do the asme for the suffix, just in reverse order
        for (int j = size-2; j >= 0; j--) 
            suffix[j] = suffix[j+1] * nums[j+1];

        //update an answer array with what we've got from both the prefix and suffix arrays
        for (int k = 0; k < size; k++)
            ans[k] = prefix[k] * suffix[k];

        return ans;
    }
};

class Solution_128 {
public:
    int longestConsecutive(std::vector<int>& nums) {
        //the idea here is to use a map to update each item and each consecutive item in a map
        //this way, we can key them based on the number in that array and allow us to keep track of every consecutive one 
        //more easily
        std::unordered_map<int, int> ans;
        int maxLength = 0;
        for (auto item: nums) {
            //if the item doesn't exist already, create it. this helps us ignore duplicates 
            if (!ans[item]) {
                //we treat everything as an island of sorts. we set the number to 1 if we haven't seen it already, otherwise
                //we use item + 1 or item - 1 depending on which consecutive numbers we've seen already. this will help us
                //"build" out the islands as we make them and we can continue to increment them as new ones get added because
                //maps and keying makes the process easier
                ans[item] = ans[item - 1] + ans[item + 1] + 1;
                ans[item - ans[item - 1]] = ans[item];
                ans[item + ans[item + 1]]  = ans[item];
                
                //take the max length of the final addition to our islands
                maxLength = std::max(maxLength, ans[item]);
            }
        }
        return maxLength;
    }
};

class Solution_198 {    
public:
    //this is not an ideal way to instantiate the data, but it works well for the solution for the purposes
    //of keeping track of where we are at all times. you could also reasonably pass by reference and it would
    //probably be more data efficient
    std::map<int, int> ansmap;
    std::vector<int> ans;
    
    //helper iterative function to determine if we can rob a certain index in the vector
    int check(int money) {
        if (money == 0) return ans[0];
        if (money == 1) return std::max(ans[0], ans[1]);
        
        //if we don't find the money within our indexed map, we simply add to where it should be,
        //iteratively calling the helper function each time based on the forward and backward index 
        //of what we're looking for
        auto itr = ansmap.find(money);
        if (itr == ansmap.end()) {
            ansmap.emplace(money, std::max(check(money - 1), check(money - 2) + ans[money]));
        }
        
        //return whatever is at our index in the map
        return ansmap.at(money);
    }
       
    int rob(std::vector<int>& nums) {
        ans = nums;
        return check(nums.size() - 1);
    }
};

class Solution_213 {
public:

    //similar to 198, we have to recursively go through each house to check for maximum output,
    //this time with the caveat that the first and last house are connected despite them not technically
    //being connected, so we can't just assume we can loot from the first or last house while ignoring
    //the other. we can account for this by rewriting the algorithm a bit
    int rob(std::vector<int>& nums) {
        if (nums.size() == 0) return 0;
        if (nums.size() == 1) return nums[0];
        int numSize = nums.size();
        return std::max(checkHouse(nums, 0, numSize - 2), checkHouse(nums, 1, numSize - 1));
    }

    //helper function. tehcnically this would be better if we passed in a copy of a vector as opposed
    //to passing in the original by reference for data integrity, but for the purposes of this problem
    //its irrelevant
    int checkHouse(std::vector<int>& neighbor, int start, int end) {
        //we create a temporary vector filled with -1s based on the size of the vector we're looking at
        //one for when we ignore the first house and another when we ignore the second
        int n = end - start + 1;
        std::vector<int> temp(n, -1);

        //we start at the start index instead of our start to support each of the two runs that we call
        temp[0] = neighbor[start];
        temp[1] = std::max(neighbor[start+1], temp[0]);

        //effectively the same as the previous problem, but now we're just using the vector we were
        //provided instead of a map, filling out the temporary vector
        for ( int i = 2; i < n; i++) 
            temp[i] = std::max(neighbor[start + i] + temp[i - 2], temp[i-1]);

        //return whichever is higher
        return std::max(temp[n-1], temp[n-2]);
    }
};

int main() {
	//Problem 238: Return array with all entries being a product of every other entry in that list
    //Problem 128: Return the length of the longest consecutive numbers list in a list
    //Problem 198: Return the highest amount of money in an array given some parameters without getting caught 
    //Problem 213: Return the highest amount of money in an array without getting caught, now circular
}