# Rectangle Class: C++ Take-Home Assignment

## Problem Statement

Design a class called `Rectangle` with private members `width` and `length`.

The class should have public member functions for getting and setting the width and length, as well as functions for calculating the area and perimeter.

In the `main` function, create suitable examples that demonstrate creating `Rectangle` objects, setting and retrieving their dimensions, and calculating their area and perimeter.

## Design Decisions

- **Encapsulation:** `width` and `length` are private, so they can only be changed through the setters.
- **Validation:** The setters reject zero and negative values by throwing `std::invalid_argument`. The parameterized constructor uses the setters, so it applies the same checks.
- **`const` correctness:** The getters and the area and perimeter functions don't modify the object, so they are marked `const`.
- **`double` type:** Dimensions can be fractional (for example, 10.5).

## What `main()` Demonstrates

1. Creating a rectangle with the default constructor.
2. Creating a rectangle with specific dimensions (5 x 3).
3. Changing dimensions with `setWidth()` and `setLength()`, then reading them back with the getters.
4. Calculating area and perimeter for each rectangle.
5. Handling an invalid value (a negative width) and showing the object is left unchanged.

## Build and Run

Requires a C++ compiler with C++11 support or later (g++, clang++, or MinGW-w64).

```bash
g++ -std=c++17 -Wall -Wextra -o rectangle rectangle.cpp
./rectangle
```

On Windows (Command Prompt or PowerShell):

```bash
g++ -std=c++17 -Wall -Wextra -o rectangle.exe rectangle.cpp
rectangle.exe
```

## Sample Output

```text
Rectangle 1 (default)
  Width:     1
  Length:    1
  Area:      1
  Perimeter: 4

Rectangle 2 (5 x 3)
  Width:     5
  Length:    3
  Area:      15
  Perimeter: 16

Rectangle 1 after setWidth(10.5) and setLength(4.0)
  Width:     10.5
  Length:    4
  Area:      42
  Perimeter: 29

Error caught: Width must be greater than zero.
Rectangle 2 width is still 5
```
