---
tags: 
title: "Basics"
author: Aarav Shah
status: 
date: "15 Mar 2025"
time: "12:03"
---
-----
### 1. Hashing Theory
###### Description

---
```Python

```
---
### 2.1 Count frequency of each element in the array using 2 Loops 
Approach:
- Make a visited array of type boolean.
- Use the first loop to point to an element of the array.
- Initialise the variable count to 1.
- Make that index true in the visited array.
- Run second loop, if we find the element then mark the visited index true and increase the count.
- If the visited index is already true then skip the other steps.

- [ ] Time Complexity - O(N^2)
- [ ] Space Complexity - O(N)

---
```Python
def count_Frequency(arr, n):
	visited = [False] * n
	for i in range(n):
	if (visited[i] == True):
		continue
	count = 1
	for j in range(i + 1, n):
		if (arr[i] == arr[j]):
			visited[j] = True
			count += 1
	print(arr[i], count)


if __name__ == '__main__':
	arr = [10,5,10,15,10,5]
	n = len(arr)
	count_Frequency(arr, n)
```
---
### 2.2 Count frequency of each element in the array using Map
###### Approach
- Take a unordered_map/HashMap of <Integer, Integer> pair.
- Use a for loop to iterate the array.
- If the element is not present in the map then insert it with frequency 1, otherwise increase the existing frequency by 1.
- Print the value frequency pair.

- [ ] Time Complexity - O(N)
- [ ] Space Complexity - O(N)
---
```Python
def Frequency(arr, n):
    mp = {}
    for i in range(n):
        if arr[i] in mp:
            mp[arr[i]] += 1
        else:
            mp[arr[i]] = 1
    for x in mp:
        print(x, mp[x])


if __name__ == '__main__':
    arr = [10, 5, 10, 15, 10, 5]
    n = len(arr)
    Frequency(arr, n)
```
---

### 3. Find the highest/lowest frequency element using Brute-Force (2 Loops approach)
###### Approach
We will be using the same countFreq() function used in the previous article with slight modifications. We will use two loops, in which, the first loop will be used to iterate the given array. Selecting an element, we will use the second loop to traverse the remaining array to find the frequency(i.e. The number of times the element occurs in the array) of the selected element i.e. arr[i]. Now after the second loop completes traversing we will keep a track of the element with the highest and lowest frequency. We also have to maintain a visited array so that it will keep track of the duplicate elements that we already count.

The steps are as follows:
- Make a visited array of type boolean.
- Use the first loop to point to an element of the array.
- Initialize the variable count to 1.
- Make that index true in the visited array.
- Run the second loop, if we find the element then mark the visited index true and increase the count.
- If the visited index is already true then skip the other steps.
- After step 5, we will keep a track of the element with the highest frequency and the lowest frequency.

- [ ] Space Complexity: 
- [ ] Time Complexity: 

---
```Python

```
---
