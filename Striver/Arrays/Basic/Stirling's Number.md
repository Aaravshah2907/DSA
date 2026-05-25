---
tags:
  - maths
  - medium
  - tree
title: Stirling's Number
author: Aarav Shah
status:
date: 21 May 2026
time: 18:05
Space Compl.:
Time Compl.:
---

-----
### Optimal Solution
###### Description

---
```cpp
int rearrangeSticks(int n, int k) {
	if (k > n || k == 0) return 0;
	long long MOD = 1e9 + 7;
	// dp[i][j] represents number of ways to arrange i sticks with j visible
	// We use a 1D vector to optimize space to O(k)

	vector<long long> dp(k + 1, 0);
	dp[0] = 1;
	
	for (int i = 1; i <= n; ++i) {
		vector<long long> next_dp(k + 1, 0);
		for (int j = 1; j <= k; ++j) {
			// S(i, j) = S(i-1, j-1) + (i-1) * S(i-1, j)
			next_dp[j] = (dp[j - 1] + (long long)(i - 1) * dp[j]) % MOD;
		}
		dp = next_dp;
	}
	return (int)dp[k];
}
```
---
