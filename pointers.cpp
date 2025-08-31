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
        if (nums.empty()) return true;

        int key, j;
        //loop through the array once
        for (int i = 0; i < nums.size(); i++) {
            //take the key that we're comparing to 
            key = nums[i];
            j = i - 1;

            //make sure we're not going out of bounds and check if the jth element in the array is greater than our key 
            while (j >= 0 && nums[j] >= key) {
                //if its the same as our key, we leave early
                if (nums[j] == key)
                    return true;
                nums[j+1] = nums[j];
                j--;
            }
            nums[j+1] = key;
        }
        return false;
    }
};

class Solution_16 {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        if (nums.size() <= 0) return 0;
        sort(nums.begin(), nums.end());
        int thirdNum = 0, start = 0, end = 0, result = 0, diff = std::numeric_limits<int>::max();

        //for every element in the sorted array
        for (int i = 0; i < nums.size() - 1; i++) {
            //set three nums, the one you're looking at, and a start and end pointer
            thirdNum = nums[i];
            start = i+1;
            end = nums.size() - 1;
            //while the start, which is the smallest non-unit value, is greater than the end, the greatest non-unit value
            while (start < end) {
                //get the sum
                int sum = (thirdNum + nums[start] + nums[end]);
                //if the sum is exactly the target, return that value, we dont need to do anything else
                if (sum == target)
                    return target;
                //otherwise, update the absolute value of the differnce
                if (abs(sum - target) < diff) {
                    diff = abs(sum - target);
                    result = sum;
                }
                
                //update the start and end pointers accordingly
                if (sum > target)
                    end--;
                else
                    start++;
                }
            }
        return result;
    }
};

class Solution_15 {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        if (nums.size() <= 2) return {};
        std::vector<std::vector<int>> result;

        //we first sort the vector to traverse it easier
        stable_sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size() - 2; i++) {
            if (i > 0 && nums[i] == nums[i-1])
                continue;

            //we use a two pointer solution to look through the array
            int ptrone = i + 1;
            int ptrtwo = nums.size() - 1;

            while (ptrone < ptrtwo) {
                int sum = nums[i] + nums[ptrone] + nums[ptrtwo];
                if (sum < 0)
                    ptrone += 1;
                else if (sum > 0)
                    ptrtwo -= 1;
                else {
                    //if we continusouly iterate and find that the sum equals 0, we push the resulting
                    //array to the result vector with the number's we're looking for, using our pointers
                    //to extract the correct numbers
                    std::vector<int> temp = {nums[i], nums[ptrone], nums[ptrtwo]};
                    result.push_back(temp);
                    while (ptrone < ptrtwo && nums[ptrone] == nums[ptrone + 1]) ptrone++;
                    while (ptrone < ptrtwo && nums[ptrtwo] == nums[ptrtwo - 1]) ptrtwo--;
                    ptrone += 1;
                    ptrtwo -= 1;
                }
            }
        }

        return result;
     }
};

int main() {
	//Problem 18:  Return unique quadruplets in list based on their sum being equal to the target number
    //Problem 217: Check if all elements in an array are unique
    //Problem 16:  Find three integers in a list such that the sum is closest to a target int
    //Problem 15:  Find all triples in a list such that i != j, j != k, k != i, and the sum of all numbers is 0
}