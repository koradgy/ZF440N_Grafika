#include <stdio.h>

void shift_matrix(int matrix[10][10], int rows, int cols, int offset)
{
    int i, j, k;
    int transformation_matrix[10][10];

    // A transzformációs mátrix elkészítése
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (i == j) {
                transformation_matrix[i][j] = 1;
            } else {
                transformation_matrix[i][j] = 0;
            }
        }
    }
    transformation_matrix[0][cols-offset] = 1;
    for (k = 1; k < offset; k++) {
        transformation_matrix[k][cols-offset+k] = 1;
    }

    // Az eredeti mátrix szorzása a transzformációs mátrixszal
    int temp_matrix[10][10];
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            temp_matrix[i][j] = 0;
            for (k = 0; k < cols; k++) {
                temp_matrix[i][j] += transformation_matrix[i][k] * matrix[k][j];
            }
        }
    }
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = temp_matrix[i][j];
        }
    }
}

int main()
{
    int matrix[10][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = 3;
    int cols = 3;
    int offset = 1;

    printf("Matrix before shifting:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    shift_matrix(matrix, rows, cols, offset);

    printf("Matrix after shifting:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
