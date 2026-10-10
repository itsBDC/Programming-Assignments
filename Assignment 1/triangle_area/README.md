### OOP Concepts Used
This program uses procedural logic and relies on standard sequential execution. No object-oriented programming (OOP) constructs are utilized.

### Algorithm
1. Prompt the user via the console to input the x and y Cartesian coordinates for three distinct points.
2. Compute the lengths of all three sides of the triangle using the Euclidean distance formula, applying the `pow` and `sqrt` functions from the `<cmath>` library.
3. Calculate the semi-perimeter `s` by summing the three side lengths and dividing the result by 2.
4. Calculate the final area using Heron's formula and display the result to the user.

### Possible Error Points
* **Input Validation:** The code uses `cin >>` without validating the input type. If a user inputs a character or string instead of a `double`, the stream will fail, resulting in garbage values or an infinite loop if placed inside a larger program.
* **Collinear Points (Floating-Point Imprecision):** If the user enters three points that form a straight line, the area should theoretically be 0. However, due to floating-point rounding errors during distance calculations, the term inside the outer `sqrt` could evaluate to an infinitesimally small negative number, causing the function to output `NaN` (Not a Number).