#include <string>

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

int main() {
	//Problem 5: Find the longest palindrome in a string
}