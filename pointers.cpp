#include <vector>
#include <algorithm>

class Solution_18 {
public:
    std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
        //is there more than 4 entries in the vector? if so, return early
        if (nums.size() <= 4) return std::vector<std::vector<int>>();
        std::vector<std::vector<int>> result;

        //we use 4 pointers to get this answer
        
        //sort the vector
        std::sort(nums.begin(), nums.end());

        //first iteration through the vector
        //this is also the first pointer, which should look at the first element
        for (int i = 0; i < nums.size(); i++) {
            //are we looking at an element beyond the first? if so, skip it
            if (i > 0 && nums[i] == nums[i-1]) continue;
            //set the second pointer to the second element
            for (int j = i+1; j < nums.size(); j++) {
                if (j > (i + 1) && nums[j] == nums[j-1]) continue;
                
                //the third pointer is simply the next element after the second
                int k = j + 1;
                //the last pointer is the final element of the vector
                int l = nums.size()-1;

                while (k < l) {
                    //get the sum of the pointers we found
                    int ansSum = nums[i] + nums[j] + nums[k] + nums[l];
                    if (ansSum == target) {
                        //push the elements as a vector to the answer list if the sum is equal to the target
                        std::vector<int> tempVec = {nums[i], nums[j], nums[k], nums[l]};
                        result.push_back(tempVec);
                        
                        //increment the third pointer and decrement the fourth, to continue looking at the list
                        k++;
                        l--;

                        //gets rid of duplicates
                        while (k < l && nums[k] == nums[k-1]) k++;
                        while (k < l && nums[l] == nums[l+1]) l--;
                    }
             
                    //if the sum is lower than the target, increment the third pointer
                    //if its higher, decrement the fourth
                    if (ansSum < target)
                        k++;
                    if (ansSum > target)
                        l--;
                }
            }
        }

        return result;
    }
};

class Solution_217 {
public:
    bool containsDuplicate(std::vector<int>& nums) {
        //base case
        if (nums.empty()) {
            return true;
        }

        int key, j;
        //loop through the array once
        for (int i = 0; i < nums.size(); i++) {
            //take the key that we're comparing to 
            key = nums[i];
            j = i - 1;

            //make sure we're not going out of bounds and check if the jth element in the array is greater than our key 
            while (j >= 0 && nums[j] >= key) {
                //if its the same as our key, we leave early
                if (nums[j] == key) {
                    return true;
                }
                nums[j+1] = nums[j];
                j--;
            }
            nums[j+1] = key;
        }
        return false;
    }
};

int main() {
	//Problem 18: Return unique quadruplets in list based on their sum being equal to the target number
    //Problem 217: Check if all elements in an array are unique
}