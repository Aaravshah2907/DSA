---
tags: 
title: Sorting
author: Aarav Shah
status: 
date: 15 Mar 2025
time: 12:03
---

-----
### 1. Selection Sort
###### Approach:
The algorithm steps are as follows:
- First, we will select the range of the unsorted array using a loop (say i) that indicates the starting index of the range. The loop will run forward from 0 to n-1. The value i = 0 means the range is from 0 to n-1, and similarly, i = 1 means the range is from 1 to n-1, and so on. (Initially, the range will be the whole array starting from the first index.)
- Now, in each iteration, we will select the minimum element from the range of the unsorted array using an inner loop.
- After that, we will swap the minimum element with the first element of the selected range(in step 1).
- Finally, after each iteration, we will find that the array is sorted up to the first index of the range.

###### **Note:** Here, after each iteration, the array becomes sorted up to the first index of the range. That is why the starting index of the range increases by 1 after each iteration. This increment is achieved by the outer loop and the starting index is represented by variable i in the following code. And the inner loop(i.e. j) helps to find the minimum element of the range [i…..n-1].

---
```Python

```
---
### Sub-Topic 2
###### Description

---
```Python

```
---
### Sub-Topic 3
###### Description

---
```Python

```
---

### Sub-Topic 4
###### Description

---
```Python

```
---
