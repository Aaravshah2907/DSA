---
tags:
  - maths
  - query
  - greedy
  - medium
title: Interior Points of a Circle via query
author: Aarav Shah
status:
date: 22 May 2026
time: 11:05
Space Compl.:
Time Compl.:
---

-----
### Optimal Solution
###### Description
All possible combinations were tried and tested in this case.

---
```cpp
class Solution {
public:
	bool inside(int xq, int yq, int xp, int yp, int r){
		bool inside = false;
		int distance = (xq-xp)*(xq-xp) + (yq-yp)*(yq-yp) - r*r;
		if (distance > 0) return false;
		return true;
	}
		
	vector<int> countPoints(vector<vector<int>>& points, vector<vector<int>>& queries) {
		vector <int> answer;
		for (vector<int> query : queries){
			int xq = query[0], yq = query[1], r = query[2];
			int count = 0;
			for (vector<int> point : points){
			int xp = point[0], yp = point[1];
				if (inside(xq,yq,xp,yp,r)){
					count++;
				}
			}
			answer.push_back(count);
		}
		return answer;
	}
};
```
---
