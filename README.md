# Burster-AED
Work developed for the Algorithms and Data Structures course from Instituto Superir Técnico

# Objective
Program developed with the objective of solving puzzles made of different color pieces. Groups of pieces of the same color form **clusters** that must be removed in order to solve the puzzle successfully.

# Variants
- **1:** Simple removal of the clusters
- **2:** Find the sequence of plays that allows to obtain a minimum score
- **3:** Find the sequence of plays that allows to obtain the maximum score

# Execution
To run the code just type `./burster <problem>.puz`. Where `<problem>` is the name of the file containing the puzzle to solve.
- This file **must** have extension `.puz` and and the first line has the following format:
  - **L C V :** where **L** and **C** are the number of rows and columns, respectively, and **V** is the variant type.

# Results
The program should create a solution file with same name of the `.puz` file but with the extension `.moves`. The first line should also correspond to the first line of the `.puz` file and in the next line, the number of moves and the obtained score. The next lines represent the moves performed in order to solve the puzzle.
