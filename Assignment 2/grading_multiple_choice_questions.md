### OOP Concepts Used
This program is entirely procedural and relies on standard control structures and primitive data types[cite: 5]. No Object-Oriented Programming (OOP) concepts are used in this solution[cite: 5].

### Algorithm
1. Initialize a 2D character array holding the multiple-choice answers for 8 students across 10 questions[cite: 5].
2. Initialize a 1D character array containing the 10 correct answer keys[cite: 5].
3. Use a nested `for` loop structure to iterate through the data: the outer loop iterates through each student, while the inner loop iterates through their respective answers[cite: 5].
4. During the inner loop, compare the student's answer at the current index to the answer key at the same index, incrementing a score counter for every exact match[cite: 5].
5. Print the student's ID (index) and their total correct score to the console before moving to the next student[cite: 5].

### Possible Error Points
* **Case Sensitivity:** The evaluation strictly uses the `==` operator for characters[cite: 5]. If an answer were recorded in lowercase (e.g., 'a' instead of 'A'), the program would mark it as incorrect.
* **Hardcoded Dimensions:** The program relies on strict constants (`NUMBER_OF_STUDENTS = 8` and `NUMBER_OF_QUESTIONS = 10`) that must perfectly match the initialized 2D array sizes[cite: 5]. Modifying the array contents without updating these constants will lead to either missed grading or out-of-bounds memory access.