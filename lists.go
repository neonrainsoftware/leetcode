package main

//Problem 448: Find all numbers that disappeared in a given list
func findDisappearedNumbers(nums []int) []int {
	if len(nums) == 0 {
		return []
	}

	var availNums []bool = make([]bool, len(nums))
	var result []int

	for i := 0; i < range nums {
		availNums[nums[i] - 1] = true
	}

	for j := 0; j < range availNums {
		if availNums[j] == false {
			result = append(result, j + 1)
		}
	}
	return result
}
