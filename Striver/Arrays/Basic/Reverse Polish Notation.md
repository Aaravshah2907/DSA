---
tags:
  - medium
  - maths
  - array
  - stack
  - graph
title: Reverse Polish Notation
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
RPN, also known as postfix notation, is designed to be parsed from left to right without needing parentheses to define operator precedence.  

1. **Iterate** through each token in the list.  
2. **If the token is an operand (a number):** Push it onto the stack.  
3. *If the token is an operator (+, -, , /):_ * Pop the top two operands from the stack.  
    • Perform the operation. **Crucially**, the first element popped is the right operand, and the second is the left operand.  
    • Push the result back onto the stack.  
4. **Result:** After processing all tokens, the stack will contain exactly one element, which is the final result.
---
```cpp
#include <vector>
#include <string>
#include <stack>

class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens) {
        std::stack<int> s;
        
        for (const std::string& token : tokens) {
            // Check if the token is an operator
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int right = s.top(); s.pop();
                int left = s.top(); s.pop();
                
                if (token == "+") s.push(left + right);
                else if (token == "-") s.push(left - right);
                else if (token == "*") s.push(left * right);
                else if (token == "/") s.push(left / right);
            } else {
                // Token is a number
                s.push(std::stoi(token));
            }
        }
        
        return s.top();
    }
};
```
---
