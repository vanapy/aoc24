#include <stdio.h>
#include <stdlib.h>

void get_dimensions(FILE* file, int* rows, int* cols) {
    *rows = 0;
    *cols = 0;
    int chars_in_first_row = 0;
    int c;
    int is_first_row = 1;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            (*rows)++;
            if (is_first_row) {
                *cols = chars_in_first_row;
                is_first_row = 0;
            }
        }
        else if (is_first_row) {
            chars_in_first_row++;
        }
    }

    // Handle last line if it doesn't end with \n
    if (chars_in_first_row > 0 && c == EOF) {
        (*rows)++;
    }

    // Return file pointer to beginning
    rewind(file);
}

char** read_matrix(const char* filename, int* rows, int* cols) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\n");
        return NULL;
    }

    // First pass: count rows and cols
    get_dimensions(file, rows, cols);

    // Allocate memory
    char** matrix = malloc(*rows * sizeof(char*));
    for (int i = 0; i < *rows; i++) {
        matrix[i] = malloc(*cols * sizeof(char));
    }

    // Second pass: read the matrix
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            char c = fgetc(file);
            if (c == '\n') {
                c = fgetc(file);
            }
            matrix[i][j] = c;
        }
    }

    fclose(file);
    return matrix;
}


int check_letter(char** matrix, int i, int j, int rows, int cols) {
    int result = 0;
    if (matrix[i][j] == 'X') {
        if ((i + 3 < rows) && (matrix[i + 1][j] == 'M') && (matrix[i + 2][j] =='A') && (matrix[i + 3][j] =='S')) {
            result++;
        }
        if ((i > 2) && (matrix[i - 1][j] == 'M') && (matrix[i - 2][j] =='A') && (matrix[i - 3][j] =='S')) {
            result++;
        }
        if ((j + 3 < cols) && (matrix[i][j + 1] == 'M') && (matrix[i][j + 2] =='A') && (matrix[i][j + 3] =='S')) {
            result++;
        }
        if ((j > 2) && (matrix[i][j - 1] == 'M') && (matrix[i][j - 2] =='A') && (matrix[i][j - 3] == 'S')) {
            result++;
        } if (
            (i + 3 < rows) && (j + 3 < cols) &&
            (matrix[i + 1][j + 1] == 'M') && (matrix[i + 2][j + 2] =='A') && (matrix[i + 3][j + 3] =='S')
        ) {
            result++;
        }
        if (
            (i > 2) && (j > 2) && (matrix[i - 1][j - 1] == 'M') &&
            (matrix[i - 2][j - 2] == 'A') && (matrix[i - 3][j - 3] == 'S')
        ) {
            result++;
        }
        if (
            (i > 2) && (j + 3 < cols) && (matrix[i - 1][j + 1] == 'M') &&
            (matrix[i - 2][j + 2] == 'A') && (matrix[i - 3][j + 3] == 'S')
        ) {
            result++;
        }
        if (
            (i + 3 < rows) && (j > 2) && (matrix[i + 1][j - 1] == 'M') &&
            (matrix[i + 2][j - 2] == 'A') && (matrix[i + 3][j - 3] == 'S')
        ) {
            result++;
        }
    return result;
    } else {
        return 0;
    }
}

int main() {
    int res = 0;
    int rows, cols;
    char** matrix = read_matrix("inputs/day_four.txt", &rows, &cols);

    if (matrix) {
        printf("Matrix dimensions: %d x %d\n", rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (matrix[i][j] == 'X') {
                    res += check_letter(matrix, i, j, rows, cols);
                }
            }
        }

        // Free memory
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
    printf("%d ", res);
    return 0;
}
