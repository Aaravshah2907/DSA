# Cheat Sheet

## Include Statements

```cpp 
#include <iostream>         // Need for Input - Output
#include <limits>           //

```

## Standard Input/Output

```cpp
std::cout << "Hello World."; // Std Output
std::cout << " Dummy!" << std::endl; // std::endl will cause the cursor to move to the next line

int n;
std::cin >> n; // Std Input for integer / any data type;
std::cin.clear(); // reset any error flags
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find a newline
std::cin.get(); // get one more char from the user (waits for user to press enter)
```

## Compilation

```bash
g++ -c main.cpp
g++ -c func1.cpp
g++ main.o func1.o -o runfile
./runfile <arg1> <arg2> ...
```


## Variable Declaration & Initialization in the Same Step.
```cpp
int width { 5 };    // define variable width and initialize with initial value 5
int a;         // default-initialization (no initializer)

// Traditional initialization forms:
int b = 5;     // copy-initialization (initial value after equals sign)
int c ( 6 );   // direct-initialization (initial value in parenthesis)

// Modern initialization forms (preferred):
int d { 7 };   // direct-list-initialization (initial value in braces)
int e {};      // value-initialization (empty braces)
```

## Unused Variables

```cpp
[[maybe_unused]] double pi { 3.14159 };  // Don't complain if pi is unused
```

