#include <vector>

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



int main() {
	//Problem 238: Return array with all entries being a product of every other entry in that list
}