---
tags:
  - medium
  - array
  - searching
title: Modified Binary Search for Rotated Array
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
1. Initialize `left = 0` and `right = nums.length - 1`.  

2. While `left <= right`:  
    • Calculate `mid = left + (right - left) / 2`.  
    • If `nums[mid] == target`, return `mid`.  
    • **Check which half is sorted:**  
    • If `nums[left] <= nums[mid]`: The left half is sorted.  
    • If `target` is within the range `[nums[left], nums[mid])`, eliminate the right half (`right = mid - 1`).  
    • Otherwise, search the right half (`left = mid + 1`).  
    • Else: The right half must be sorted.  
    • If `target` is within the range `(nums[mid], nums[right]]`, eliminate the left half (`left = mid + 1`).  
    • Otherwise, search the left half (`right = mid - 1`).  

3. If the loop finishes without finding the target, return `-1`.
---
```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            }

            // Check if the left half is sorted
            if (nums[left] <= nums[mid]) {
                // Target is in the left sorted portion
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } 
            // Otherwise, the right half must be sorted
            else {
                // Target is in the right sorted portion
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
```
---
