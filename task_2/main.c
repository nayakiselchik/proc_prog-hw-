#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", *(arr + i * n + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int arr[N][N];
    int rowZero[N] = {0};
    int colZero[N] = {0};

    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *(arr[i] + j) = rand() % 11;
            if (*(arr[i] + j) == 0) {
                rowZero[i] = 1;
                colZero[j] = 1;
            }
        }
    }

    printf("Original array:\n");
    printArray(&arr[0][0], N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (rowZero[i] == 1 || colZero[j] == 1) {
                *(arr[i] + j) = 0;
            }
        }
    }

    printf("Modified array:\n");
    printArray(&arr[0][0], N);

    return 0;
}
