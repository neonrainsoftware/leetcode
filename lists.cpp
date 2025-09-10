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

class Solution_152 {
public:
    int maxProduct(std::vector<int>& nums) {
        if (nums.size() == 0) return 0;

        //this approach relies on two "pointers", one that starts at the end of the list and the other
        //at the beginning, as well as a variable that tracks the result
        int prefix = 1, suffix = 1;
        int result = INT_MIN;

        for (int i = 0; i < nums.size(); i++) {
            //set the prefix and suffix to the product for each number we see, the prefix starting from the 
            //start and the suffix at the end
            prefix *= nums[i];
            suffix *= nums[nums.size() - i - 1];

            //get the max between result, suffix, and prefix (for some reason, C++ wants to pass this in
            //as an object as opposed to just accepting more optional parameters)
            result = std::max({result, suffix, prefix});

            //if we encounter a 0 during any point for either the prefix or suffix, set the result to 1
            //because we've already saved the value from the previous integers, so now the rest of the
            //sequence doesn't matter because the product will always be 0
            if (prefix == 0) prefix = 1;
            if (suffix == 0) suffix = 1;
        }

        return result;
    }
};

class Solution_41 {
public:
    int firstMissingPositive(std::vector<int>& nums) {
        if (nums.size() <= 0) return 0;

        for (int i = 0; i < nums.size(); i++) {
            int temp = nums[i];
 
            while ((temp >= 1 && temp <= nums.size()) && temp != i + 1 && nums[temp-1] != temp) {
                //we're swapping the nums as that would effectively be the best way to sort the list
                //you could theoretically just use the built-in sort function, but this way we can control
                //exactly how we sort it
                std::swap(nums[temp-1], nums[i]);
                temp = nums[i];
            }
        }
        for (int j = 0; j < nums.size(); j++) {
            //is the number at this position supposed to be the next natural progression at that point
            //in that list? if so, skip it. otherwise, return the that number + 1 as the missing positive
            //number in that list
            if (nums[j] == j + 1)
                continue;
            return j + 1;
        }

        //if the list is correct by the time we got to this point, simply return the last element in the
        //list + 1 as that would be the next missing number
        return nums[nums.size() - 1] + 1;
    }
};

class Solution_81 {
public:
    bool search(std::vector<int>& nums, int target) {
        if (nums.size() == 0) return false;

        int numSize = nums.size();
        int leftPtr = 0, rightPtr = numSize - 1;

        while (leftPtr <= rightPtr) {
            int mid = leftPtr + (rightPtr - leftPtr) / 2;
            if (nums[mid] == target) return true;

            if (nums[leftPtr] == nums[mid] && nums[rightPtr] == nums[mid]) {
                leftPtr++;
                rightPtr--;
                continue;
            }

            if (nums[leftPtr] > nums[mid]) {
                if (nums[mid] <= target && nums[rightPtr] >= target)
                    leftPtr = mid + 1;
                else
                    rightPtr = mid - 1;
            } else {
                if (nums[mid] >= target && nums[leftPtr] <= target)
                    rightPtr = mid - 1;
                else 
                    leftPtr = mid + 1;
            }
        }
        return false;
    }
};

class Solution_57 {
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        if (intervals.size() == 0) return intervals;

        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end());

        std::vector<std::vector<int>> result;
        result.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            if (result.back()[1] >= intervals[i][0]) 
                result.back()[1] = std::max(result.back()[1], intervals[i][1]);
            else
                result.push_back(intervals[i]);
        }

        return result;
    }
};

class Solution_162 {
public:
    int findPeakElement(std::vector<int>& nums) {
        if (nums.size() == 0) return 0;

        //fairly classic binary search algorithm implementation
        int leftPtr = 0, rightPtr = nums.size() - 1;

        while (leftPtr < rightPtr) {
            //DO NOT FORGET THIS, will cause integer overflow issues if left out
            int midPtr = leftPtr + (rightPtr - leftPtr) / 2;
            
            //if the middle of the list is greater than the one next to it on its right, then increment
            //the left by the mid. the left will serve as our index and we don't have to keep track of
            //it separately with a data structure. if its not, than we set the right to the middle. 
            //this works because it immediately tracks if its the peak element beacuse of the way it
            //checks the next element
            if (nums[midPtr] < nums[midPtr+1])
                leftPtr = midPtr + 1;
            else
                rightPtr = midPtr;
        }

        return leftPtr;
    }
};

class Solution_2022 {
public:
    std::vector<std::vector<int>> construct2DArray(std::vector<int>& original, int m, int n) {
        if (original.size() == 0 || (n > m && original.size() < n)) return {};

        std::vector<std::vector<int>> result;
        std::vector<int> temp;
        int ptrOne = n, ptrTwo = m;

        for (int i = 0; i < original.size(); i++) {
            temp.push_back(original[i]);
            ptrOne--;
            if (ptrOne == 0 || i == original.size() - 1) {
                result.push_back(temp);
                temp.clear();
                ptrOne = n;
                ptrTwo--;
            }
        }

        if (ptrTwo == 0) return result;
        return {};
    }
};

class Solution_238 {
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

class Solution_643 {
public:
    double findMaxAverage(std::vector<int>& nums, int k) {
        if (nums.size() < k) return 0;

        //initiate a sliding window so that we can provide ourselves with a baseline. we only
        //care about the initial sum because we can always divide the full answer by k at the
        //end anyway and we just need the maximum number
        double temp = nums[0];
        for (int j = 1; j < k ; j++) {
            temp += nums[j];
        }

        //once we have the baseline, run through the rest of the vector using a sliding window
        //to determine which of the numbers is biggest by the end
        double result = temp;
        for (int i = k; i < nums.size(); i++) {
            temp += nums[i] - nums[i - k];
            result = std::max(result, temp);
        }

        //return the result divided by k
        return result / k;
    }
};

class Solution_3046 {
public:
    bool isPossibleToSplit(std::vector<int>& nums) {
        if (nums.size() == 0) return false;

        std::unordered_map<int, int> result;
        int maxCnt = 0;

        for (int i = 0; i < nums.size(); i++) {
            result[nums[i]] += 1;
            if (result[nums[i]] > maxCnt)
                maxCnt = result[nums[i]];
            if (maxCnt > 2)
                return false;
        }

        return true;
    }
};

int main() {
	//Problem 238:  Return array with all entries being a product of every other entry in that list
    //Problem 128:  Return the length of the longest consecutive numbers list in a list
    //Problem 198:  Return the highest amount of money in an array given some parameters without getting caught 
    //Problem 213:  Return the highest amount of money in an array without getting caught, now circular
    //Problem 152:  Return the highest product amongst subarrays in an array
    //Problem 41:   Find the first missing positive integer given a list of  numbers
    //Problem 81:   Search a rotated sorted array
    //Problem 57:   Insert a new interval (pair) into a list based on front and back of that new interval
    //Problem 162:  Find the peak element in a list. Must run in O(log n) time
    //Problem 2022: Create a 2D array out of a 1D array given m and n dimensions
    //Problem 238:  Return an array were array[i] is equal to the product of all other i, without using division in O(n)
    //Problem 643:  Find the maximum average of k elements in a vector
    //Problem 3046: Find out if a vector is possible to split in two, without any repeats
}