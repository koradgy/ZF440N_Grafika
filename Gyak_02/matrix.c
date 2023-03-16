#include <stdio.h>

void transform_matrix(int matrix[10][10], int rows, int cols, int scalar)
{
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = matrix[i][j] * scalar;
        }
    }
}

int main()
{
    int matrix[10][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = 3;
    int cols = 3;
    int scalar = 2;

    printf("Matrix before transformation:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    transform_matrix(matrix, rows, cols, scalar);

    printf("Matrix after transformation:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
