# Basics

## Comments

```cpp
//       -->Single Line comments
/* */ // -->Multiline Comments
```

In `VS Code` to toggle comments for multiline use `⌘ + /`

## Variables

### Declaration & Initialization in Same line

```cpp
#include <iostream>

int main()
{
	/*
	type identifier { expression };
	int x {2+3}; // Will evaluate perfectly;
	*/
    int width { 5 };    // define variable width and initialize with initial value 5
    std::cout << width; // prints 5

    return 0;
}
```

### Other Examples
```cpp
int a;         // default-initialization (no initializer)

// Traditional initialization forms:
int b = 5;     // copy-initialization (initial value after equals sign)
int c ( 6 );   // direct-initialization (initial value in parenthesis)

// Modern initialization forms (preferred):
int d { 7 };   // direct-list-initialization (initial value in braces)
int e {};      // value-initialization (empty braces)
```

### Complete Table

| Initialization Type        | Example        | Note                                                    |
| -------------------------- | -------------- | ------------------------------------------------------- |
| Default-initialization     | int x;         | In most cases, leaves variable with indeterminate value |
| Copy-initialization        | int x = 5;     |                                                         |
| Direct-initialization      | int x ( 5 );   |                                                         |
| Direct-list-initialization | int x { 5 };   | Narrowing conversions disallowed                        |
| Copy-list-initialization   | int x = { 5 }; | Narrowing conversions disallowed                        |
| Value-initialization       | int x {};      | Usually performs zero-initialization                    |

## Maybe Unused variables for better memory management

```cpp
#include <iostream>

int main()
{
    [[maybe_unused]] double pi { 3.14159 };  // Don't complain if pi is unused
    [[maybe_unused]] double gravity { 9.8 }; // Don't complain if gravity is unused
    [[maybe_unused]] double phi { 1.61803 }; // Don't complain if phi is unused

    std::cout << pi << '\n';
    std::cout << phi << '\n';

    // The compiler will no longer warn about gravity not being used

    return 0;
}
```

## Std Input/Output

```cpp
#include <iostream> // for std::cout and std::endl

int main()
{
    std::cout << "Hi!" << std::endl; // std::endl will cause the cursor to move to the next line
    std::cout << "My name is Alex." << std::endl;

    return 0;
}
```

Using `std::endl` is often inefficient, as it actually does two jobs: it outputs a newline (moving the cursor to the next line of the console), and it flushes the buffer (which is slow). If we output multiple lines of text ending with `std::endl`, we will get multiple flushes, which is slow and probably unnecessary.
To output a newline without flushing the output buffer, we use `\n` (inside either single or double quotes), which is a special symbol that the compiler interprets as a newline character. `\n` moves the cursor to the next line of the console without causing a flush, so it will typically perform better. `\n` is also more concise to type and can be embedded into existing double-quoted text.


```cpp
#include <iostream> // for std::cout

int main()
{
    int x{ 5 };
    std::cout << "x is equal to: " << x << '\n'; // single quoted (by itself) (conventional)
    std::cout << "Yep." << "\n";                 // double quoted (by itself) (unconventional but okay)
    std::cout << "And that's all, folks!\n";     // between double quotes in existing text (conventional)
    return 0;
}
```

```cpp
#include <iostream>  // for std::cout and std::cin

int main()
{
    std::cout << "Enter a number: "; // ask user for a number

    int x{};       // define variable x to hold user input (and value-initialize it)
    std::cin >> x; // get number from keyboard and store it in variable x

    std::cout << "You entered " << x << '\n';
    return 0;
}
```

```cpp
#include <iostream>

int main()
{
	std::cout << sizeof(int) << '\n'; // print how many bytes of memory an int value takes

	return 0;
}
```

## Keywords in C++

- alignas
- alignof
- and
- and_eq
- asm
- auto
- bitand
- bitor
- bool
- break
- case
- catch
- char
- char8_t (since C++20)
- char16_t
- char32_t
- class
- compl
- concept (since C++20)
- const
- consteval (since C++20)
- constexpr
- constinit (since C++20)
- const_cast
- continue
- co_await (since C++20)
- co_return (since C++20)
- co_yield (since C++20)
- decltype
- default
- delete
- do
- double
- dynamic_cast
- else
- enum
- explicit
- export
- extern
- false
- float
- for
- friend
- goto
- if
- inline
- int
- long
- mutable
- namespace
- new
- noexcept
- not
- not_eq
- nullptr
- operator
- or
- or_eq
- private
- protected
- public
- register
- reinterpret_cast
- requires (since C++20)
- return
- short
- signed
- sizeof
- static
- static_assert
- static_cast
- struct
- switch
- template
- this
- thread_local
- throw
- true
- try
- typedef
- typeid
- typename
- union
- unsigned
- using
- virtual
- void
- volatile
- wchar_t
- while
- xor
- xor_eq

## Naming Convention of Variables

```cpp
int my_variable_name;   // conventional (separated by underscores/snake_case)
int my_function_name(); // conventional (separated by underscores/snake_case)

int myVariableName;     // conventional (intercapped/camelCase)
int myFunctionName();   // conventional (intercapped/camelCase)
```

Give proper descriptive variable names for ease of reading.

If 2 Strings are next to each other without any seperator / new line seperator, they are concatenated.

```cpp
#include <iostream>

int main(){
	std::cout << "Hello "
	     "world!"; // prints "Hello world!"
}
```

If the code has very long lines

```cpp
#include <iostream>
int main()
{
    std::cout << "This is a really, really, really, really, really, really, really, "
        "really long line\n"; // one extra indentation for continuation line

    std::cout << "This is another really, really, really, really, really, really, really, "
                 "really long line\n"; // text aligned with the previous line for continuation line

    std::cout << "This one is short\n";
    
    std::cout << 3 + 4
			    + 5 + 6
			    * 7 * 8; // Operator on next line.
	
	// Good Writing Practice
	[[maybe_unused]] int cost          = 57;
	[[maybe_unused]] int pricePerItem  = 24;
	[[maybe_unused]] int value         = 5;
	[[maybe_unused]] int numberOfItems = 17; 
	
	// Good Writing Practice
	std::cout << "Hello world!\n";                  // cout lives in the iostream library
	std::cout << "It is very nice to meet you!\n";  // these comments are easier to read
	std::cout << "Yeah!\n";                         // especially when all lined up
	
	// cout lives in the iostream library
	std::cout << "Hello world!\n";
	
	// these comments are easier to read
	std::cout << "It is very nice to meet you!\n";
	
	// when separated by whitespace
	std::cout << "Yeah!\n";
}
```

## Literals & Operators

What are `”Hello world!”` and `5`? They are literals. A **literal** (also known as a **literal constant**) is a fixed value that has been inserted directly into the source code.

Literals and variables both have a value (and a type). Unlike a variable (whose value can be set and changed through initialization and assignment respectively), the value of a literal is fixed and cannot be changed. The literal `5` always has value `5`. This is why literals are called constants.

In mathematics, an **operation** is a process involving zero or more input values (called **operands**) that produces a new value (called an _output value_). The specific operation to be performed is denoted by a symbol called an **operator**.

### Arity of Operators

The number of operands that an operator takes as input is called the operator’s **arity**. Few people know what this word means, so don’t drop it in a conversation and expect anybody to have any idea what you’re talking about. Operators in C++ come in four different arities:

**Unary** operators act on one operand. An example of a unary operator is the `-` operator. For example, given `-5`, `operator-` takes literal operand `5` and flips its sign to produce new output value `-5`.

**Binary** operators act on two operands (often called _left_ and _right_, as the left operand appears on the left side of the operator, and the right operand appears on the right side of the operator). An example of a binary operator is the `+` operator. For example, given `3 + 4`, `operator+` takes the left operand `3` and the right operand `4` and applies mathematical addition to produce new output value `7`. The insertion (`<<`) and extraction (`>>`) operators are binary operators, taking `std::cout` or `std::cin` on the left side, and the value to output or variable to input to on the right side.

**Ternary** operators act on three operands. There is only one of these in C++ (the conditional operator), which we’ll cover later.

**Nullary** operators act on zero operands. There is also only one of these in C++ (the throw operator), which we’ll also cover later.

Note that some operators have more than one meaning depending on how they are used. For example, `operator-` has two contexts. It can be used in unary form to invert a number’s sign (e.g. to convert `5` to `-5`, or vice versa), or it can be used in binary form to do subtraction (e.g. `4 - 3`).

### Order of Operations

We’ll talk more about the order in which operators execute when we do a deep dive into the topic of operators. For now, it’s enough to know that the arithmetic operators execute in the same order as they do in standard mathematics: `Parenthesis first, then Exponents, then Multiplication & Division, then Addition & Subtraction`. This ordering is sometimes abbreviated _PEMDAS_, or expanded to the mnemonic “Please Excuse My Dear Aunt Sally”.

### Return Values & 'Side Effects'
In C++, the term “side effect” has a different meaning: it is an observable effect of an operator or function beyond producing a return value.

Since assignment has the observable effect of changing the value of an object, this is considered a side effect. We use certain operators (e.g. the assignment operator) primarily for their side effects (rather than the return value those operators produce). In such cases, the side effect is both beneficial and predictable (and it is the return value that is often incidental).

## Functions & Files

