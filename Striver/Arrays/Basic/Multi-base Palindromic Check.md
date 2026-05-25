---
tags:
  - maths
  - medium
  - greedy
title: Multi-base Palindromic Check
author: Aarav Shah
status:
date: 22 May 2026
time: 10:05
Space Compl.:
Time Compl.:
---

-----
### Optimal Solution
###### Description
We'll use base conversion with palindrome validation:

1. **Base iteration**: Check every base from 2 to n-2 (as required by definition)
2. **Base conversion**: For each base, convert n using repeated division and modulo operations
3. **String construction**: Build the base representation by prepending remainders
4. **Palindrome check**: Compare the string with its reverse using slicing
5. **Early termination**: Return false immediately if any base representation is not palindromic
6. **Complete validation**: Return true only if all bases produce palindromes

This approach systematically validates the palindrome property across all required bases.

---
```cpp
class Solution { 
	public: bool isStrictlyPalindromic(int n) { 
		for (int i = 2; i <= n - 2; i++) { 
			int temp = n; 
			string digits = ""; 
			while (temp > 0) { 
				int rem = temp % i; 
				digits = to_string(rem) + digits; temp /= i; 
			}
			string rev = digits; 
			reverse(rev.begin(), rev.end()); 
			if (digits != rev) return false; 
		} 
		return true; 
	} 
};

Solution.isStrictlyPalindromic(10);
```
---
