#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
#define EMPTY 0

// Function to print the Sudoku grid
void printSudoku(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0) {
            printf("------+------+------\n");
        }
        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0 && j != 0) {
                printf("| ");
            }
            printf("%2d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a value can be placed in a particular position
int canPlace(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check if the number already exists in the same row or column
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return 0;
        }
    }

    // Check if the number already exists in the same 3x3 box
    int boxStartRow = row - row % 3;
    int boxStartCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + boxStartRow][j + boxStartCol] == num) {
                return 0;
            }
        }
    }

    return 1;
}

// Function to solve the Sudoku grid using backtracking
int solveSudoku(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == EMPTY) {
                for (int num = 1; num <= SIZE; num++) {
                    if (canPlace(grid, row, col, num)) {
                        grid[row][col] = num;

                        if (solveSudoku(grid)) {
                            return 1;
                        }

                        grid[row][col] = EMPTY;
                    }
                }

                return 0;
            }
        }
    }

    return 1;
}

// Function to generate a Sudoku pattern
void generateSudokuPattern(int grid[SIZE][SIZE], int difficulty) {
    // Generate a fully solved Sudoku grid
    solveSudoku(grid);

    // Remove numbers based on the specified difficulty level
    int numToRemove = 0;
    switch (difficulty) {
        case 1:
            numToRemove = 40;
            break;
        case 2:
            numToRemove = 50;
            break;
        case 3:
            numToRemove = 60;
            break;
        default:
            numToRemove = 40;
            break;
    }

    // Randomly remove numbers from the solved grid
    srand(time(NULL));
    while (numToRemove > 0) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (grid[row][col] != EMPTY) {
            grid[row][col] = EMPTY;
            numToRemove--;
        }
    }
}

int main() {
    int grid[SIZE][SIZE] = {0};

    int difficulty;
    printf("Enter difficulty level (1-3): ");
    scanf("%d", &difficulty);

    generateSudokuPattern(grid, difficulty); // Generate Sudoku pattern with specified difficulty level

    printf("Generated Sudoku Pattern:\n");
    printSudoku(grid);

    return 0;
}
