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

//Problem 169: Find the majority element in an array
func majorityElement(nums []int) int {
    if len(nums) == 0 {
        return 0
    }

    currCnter := math.MinInt
    maxCnter := 0
    for i := 0; i < len(nums); i++ {
       if currCnter != nums[i] {
        if maxCnter <= 0 {
            maxCnter++
            currCnter = nums[i]
        } else {
            maxCnter--
        }
       } else {
        maxCnter++
       }
    }

    return currCnter
}

//Problem 3046: Find out if a vector is possible to split in two, without any repeats
func isPossibleToSplit(nums []int) bool {
    if len(nums) == 0 {
        return false
    }    

    result := make(map[int]int)
    maxCnt := 0

    for i := 0; i < len(nums); i++ {
        result[nums[i]] += 1
        if result[nums[i]] > maxCnt {
            maxCnt = result[nums[i]]
        }
        if maxCnt > 2 {
            return false
        }
    }

    return true
}
