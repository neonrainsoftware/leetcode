#include <string>
#include <math.h>
#include <unordered_set>

class Solution_5 {
public:
    std::string longestPalindrome(std::string s) {
		//if our string has a 1 or 0 length, return the string
        if (s.size() <= 1) return s;

		//set up integers for tracking
        int bestLen = 0;
        int bestStart = 0;

		//iterate through the string
        for (int i = 0; i < s.size() - 1; i++) {
            for (int j = i; j < s.size() - 1; j++) {
                
				// if we found a palindrome
				if (s[i] == s[j] && isPalindrome(s, i, j)) {
                    //check to see if its the longest one and if it is, update our trackers
					if ((j - i + 1) > bestLen) {
                        bestLen = j - i + 1;
                        bestStart = i;
                    }
                }
            }
        }

		//return the correct substring using our trackers
        return s.substr(bestStart, bestLen);
    }

	//helper function to determine if what we pass in is a palindrome
    bool isPalindrome(std::string s, char x, char y) {
        while (x <= y) {
            if (s[x++] != s[y--])
                return false;
        }

        return true;
    }
};

class Solution_3 {
public:
    int lengthOfLongestSubstring(std::string s) {
        if (s.length() == 0) return 0;

        //the ideal data structure here is an unordered set 
        std::unordered_set<char> ans;
        //i and j are effectively trackers 
        int answer = 0, i = 0, j = 0;

        while (j < s.length()) {
            //if we didnt find a substring with length j in our string 
            if (ans.find(s[j]) == ans.end()) {
                //insert the substring at that length into the set, then increment the j tracker by 1
                ans.insert(s[j++]);
                //the answer is whichever is greater, either itself or the size of our set
                answer = std::max(answer, (int)ans.size());
            }
            else {
                //if we did find a substring, simply clear the set and add a new substring into the set, 
                //then increment the i tracker by 1
                ans.erase(s[i++]);
            }
        }
        return answer;
    }
};

int main() {
	//Problem 5:   Find the longest palindrome in a string
    //Problem 3:   Find the length of the longest substring in a given string
}