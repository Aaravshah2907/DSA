---
tags:
  - hard
  - pnc
  - maths
title: Factorial Lehmar Code
author: Aarav Shah
status:
date: 21 May 2026
time: 16:05
Space Compl.:
Time Compl.:
---

-----
### Optimal Solution
###### Description
**The Mathematical Logic**  
For ‭`$n$`‬ numbers, there are ‭`$($`‬‭`$n$`‬‭`$\hphantom{}-1$`‬‭`$)$`‬‭`$!\hphantom{}$`‬ permutations that start with each specific digit. By dividing ‭`$($`‬‭`$k$`‬‭`$\hphantom{}-1$`‬‭`$)$`‬ by ‭`$($`‬‭`$n$`‬‭`$\hphantom{}-1$`‬‭`$)$`‬‭`$!\hphantom{}$`‬, we can identify which block of permutations our target lies in.  

1. **Preparation:** Maintain a list of available numbers: `[1, 2, ..., n]`.  
    
2. **Indexing:** Since ‭$k$‬ is 1-indexed, we subtract 1 from ‭$k$‬ (‭$k$ ‬‭$\hphantom{}= k$‬‭ $\hphantom{}- 1$‬) to work with 0-indexing.  
    
3. **Iteration:** For each position from ‭$n$‭ $\hphantom{}-1$‬ down to 0:  
    • Calculate the block size: `fact = factorial(i)`.  
    • Determine the index of the next number: `index = k / fact`.  
    • Pick the number at that index from our available list and append it to the result.  
    • Remove that number from the list.  
    • Update ‭$k$‬: `k = k % fact`.
---
```cpp
class Solution {
	public:
		string getPermutation(int n, int k) {
			vector<int> numbers;
			int fact = 1;
			
			// 1. Fill the list and calculate (n-1)!
			for (int i = 1; i <= n; ++i) {
				numbers.push_back(i);
				if (i < n) fact *= i;
			}
			
			k--; // Adjust to 0-indexing
			string result = "";

			// 2. Determine each digit
			for (int i = n - 1; i >= 0; --i) {
				int index = k / fact;
				result += to_string(numbers[index]);
				numbers.erase(numbers.begin() + index);
				if (i > 0) {
					k %= fact;
					fact /= i;
				}
			}
		return result;
	}
};
```
---