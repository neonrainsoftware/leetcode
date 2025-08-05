#include <vector>
#include <math.h>
#include <unordered_map>
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

int main() {
	//Problem 238: Return array with all entries being a product of every other entry in that list
    //Problem 128: Return the length of the longest consecutive numbers list in a list
}