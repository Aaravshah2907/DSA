---
aliases:
  - Introduction
tags:
  - compilation
  - terminal
  - terminology
---

# Pre-reqs

## First Code
```cpp
#include <iostream> // Need for Input - Output

int main()
{
    std::cout << "Hello World.";
    return 0;
}
```

## Std Input Flags

```cpp
std::cin.clear(); // reset any error flags
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find a newline
std::cin.get(); // get one more char from the user (waits for user to press enter)
```

## Error Number Check

```cpp
void foo(int)
{
}

int main()
{
    unsigned int x { 5 };
    foo(x);

    return 0;
}
```

## Compilation
We will use `g++` for compilation work.

Example to execute a `dummp.cpp` file by creating a specific run file ( #suggested_method):
```bash
g++ dummy.cpp -o runfile
./runfile <arg1> <arg2> ...
```

Multiple files Compilation: Compile each file individually with a `-c` flag and them compile all `.o` files with a `-o` flag.
```bash
g++ -c main.cpp
g++ -c func1.cpp
g++ main.o func1.o -o runfile
./runfile <arg1> <arg2> ...
```

It is preferred to make a `Makefile` and use that for execution instead of manually creating object and source files.

## Passing arguments via command line

```cpp
//argument.cpp
#include <iostream>

using namespace std;
int main(int argc, char * argv[])
{
    for (int i = 0; i < argc; i++)
        cout << i << ": " << argv[i] << endl;
}
```
