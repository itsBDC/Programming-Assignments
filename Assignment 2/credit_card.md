### OOP Concepts Used
This solution uses a procedural programming approach[cite: 4]. While it utilizes standard template library (STL) objects like `std::vector` and `std::string` to manage data structure, it does not define or implement custom Object-Oriented Programming (OOP) concepts such as classes, encapsulation, inheritance, or polymorphism[cite: 4].

### Algorithm
1. Prompt the user to enter a credit card number as a string and convert each character into an integer, storing them in a vector[cite: 4].
2. Evaluate the card's validity based on Luhn's algorithm by calculating the sum of every second digit from right to left (doubling them and adding their individual digits if the doubled value is 10 or greater) and adding this to the sum of the remaining odd-placed digits[cite: 4].
3. Check if the total sum is divisible by 10 without a remainder[cite: 4].
4. Verify that the card number begins with a valid prefix (4, 5, 37, or 6) and has a valid length between 13 and 16 digits[cite: 4].
5. Output whether the card is valid or invalid, along with its specific attributes (size, prefix match status, and calculated sums)[cite: 4].

### Possible Error Points
* **Non-Numeric Input:** The function `readCardNumber` reads a string and blindly subtracts `'0'` from each character[cite: 4]. If the user inputs letters or symbols, this will result in invalid integer values inside the vector, corrupting the algorithmic calculations.
* **Input String with Spaces:** The `cin >> number` extraction stops at the first whitespace[cite: 4]. If a user enters the card number with spaces (e.g., "1234 5678..."), only the first chunk will be captured and evaluated.