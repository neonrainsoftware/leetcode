#include <vector>

class Solution_136 {
public:
    int singleNumber(std::vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int result = 0;

        for (auto number : nums) 
            result ^= number;

        return result;
    }
};

int main() {
	//Problem 136: Find the single number in a list that only appears once while every other one appears twice
}