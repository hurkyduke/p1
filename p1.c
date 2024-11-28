1.
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int m, n;

    // Input size of matrix and vector
    printf("Enter the size of square matrix: ");
    scanf("%d", &n);
    printf("Enter the size of vector: ");
    scanf("%d", &m);

    // Check if multiplication is possible
    if (m != n) {
        printf("Multiplication is not possible.\n");
        return 0;
    }

    // Dynamic memory allocation
    int **arr = (int **)malloc(n * sizeof(int *));
    int *vec = (int *)malloc(n * sizeof(int));
    int *res = (int *)malloc(n * sizeof(int));

    // Initialize matrix and vector
    omp_set_num_threads(n);
    srand(time(0)); // Seed for random numbers

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            arr[i][j] = rand() % 100; // Random matrix elements
        }
        vec[i] = rand() % 100; // Random vector elements
    }

    // Matrix-vector multiplication
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        res[i] = 0;
        for (int j = 0; j < n; j++) {
            res[i] += arr[i][j] * vec[j];
        }
    }

    // Print the results
    printf("Matrix * Vector = Resultant Matrix\n");
    for (int i = 0; i < n; i++) {
        // Print matrix row
        for (int j = 0; j < n; j++) {
            printf("%3d ", arr[i][j]);
        }
        // Print vector and result
        if (i == n / 2) {
            printf("  *  %3d  = %6d\n", vec[i], res[i]);
        } else {
            printf("     %3d     %6d\n", vec[i], res[i]);
        }
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    free(vec);
    free(res);

    return 0;
}
