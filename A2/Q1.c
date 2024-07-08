#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define N 9

// Function prototypes
void percolate_down(int A[][N], int i, int j, int n);
void percolate_up(int A[][N], int i, int j, int n);

// Get neighbors up (left and above)
void getNeighborsUp(int A[][N], int i, int j, int* neighbors, int* count) {
    *count = 0;
    if (j - 1 >= 0) {
        neighbors[(*count)++] = i * N + (j - 1);
    }
    if (i - 1 >= 0) {
        neighbors[(*count)++] = (i - 1) * N + j;
    }
}

// Get neighbors down (right and below)
void getNeighborsDown(int A[][N], int i, int j, int* neighbors, int* count) {
    *count = 0;
    if (j + 1 < N) {
        neighbors[(*count)++] = i * N + (j + 1);
    }
    if (i + 1 < N) {
        neighbors[(*count)++] = (i + 1) * N + j;
    }
}

// Move up
void moveUp(int A[][N], int i, int j, int* new_i, int* new_j) {
    int neighbors[2], count, ni, nj, min_idx = -1;
    getNeighborsUp(A, i, j, neighbors, &count);
    if (count == 0) {
        *new_i = -1;
        *new_j = -1;
        return;
    }

    int min_val = A[i][j];
    for (int k = 0; k < count; k++) {
        ni = neighbors[k] / N;
        nj = neighbors[k] % N;
        if (A[ni][nj] < min_val) {
            min_val = A[ni][nj];
            min_idx = k;
        }
    }

    if (min_idx != -1) {
        ni = neighbors[min_idx] / N;
        nj = neighbors[min_idx] % N;
        int temp = A[i][j];
        A[i][j] = A[ni][nj];
        A[ni][nj] = temp;
        *new_i = ni;
        *new_j = nj;
    } else {
        *new_i = -1;
        *new_j = -1;
    }
}

// Move down
void moveDown(int A[][N], int i, int j, int* new_i, int* new_j) {
    int neighbors[2], count, ni, nj, min_idx = -1;
    getNeighborsDown(A, i, j, neighbors, &count);
    if (count == 0) {
        *new_i = -1;
        *new_j = -1;
        return;
    }

    int min_val = A[i][j];
    for (int k = 0; k < count; k++) {
        ni = neighbors[k] / N;
        nj = neighbors[k] % N;
        if (A[ni][nj] < min_val) {
            min_val = A[ni][nj];
            min_idx = k;
        }
    }

    if (min_idx != -1) {
        ni = neighbors[min_idx] / N;
        nj = neighbors[min_idx] % N;
        int temp = A[i][j];
        A[i][j] = A[ni][nj];
        A[ni][nj] = temp;
        *new_i = ni;
        *new_j = nj;
    } else {
        *new_i = -1;
        *new_j = -1;
    }
}

// Percolate down
void percolate_down(int A[][N], int i, int j, int n) {
    int new_i, new_j;
    moveDown(A, i, j, &new_i, &new_j);
    if (new_i != -1 && new_j != -1) {
        percolate_down(A, new_i, new_j, n);
    }
}

// Percolate up
void percolate_up(int A[][N], int i, int j, int n) {
    int new_i, new_j;
    moveUp(A, i, j, &new_i, &new_j);
    if (new_i != -1 && new_j != -1) {
        percolate_up(A, new_i, new_j, n);
    }
}

// Pop minimum function
int popmin(int A[][N], int n) {
    if (n == 0) {
        return -1;  // No element to pop from an empty matrix
    }

    // The smallest element is at the top-left corner (0, 0)
    int min_element = A[0][0];

    // Replace the smallest element with the bottom-right corner element
    A[0][0] = A[n-1][n-1];
    A[n-1][n-1] = INF;

    // Start percolating down from the top-left corner
    percolate_down(A, 0, 0, n);

    return min_element;
}

// Main function for testing
int main() {
    int A[N][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {10, 11, 12, 13, 14, 15, 16, 17, 18},
        {19, 20, 21, 22, 23, 24, 25, 26, 27},
        {28, 29, 30, 31, 32, 33, 34, 35, 36},
        {37, 38, 39, 40, 41, 42, 43, 44, 45},
        {46, 47, 48, 49, 50, 51, 52, 53, 54},
        {55, 56, 57, 58, 59, 60, 61, 62, 63},
        {64, 65, 66, 67, 68, 69, 70, 71, 72},
        {73, 74, 75, 76, 77, 78, 79, 80, INF}
    };

    int n = 9;
    int min_element = popmin(A, n);
    printf("Popped minimum element: %d\n", min_element);
    printf("Matrix after popmin operation:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == INF) {
                printf("INF ");
            } else {
                printf("%d ", A[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}










// Alt code:
#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define N 9

// Function prototypes
void getNeighborsDown(int A[][N], int i, int j, int *neighbors, int *count);
void moveDown(int A[][N], int i, int j, int *new_i, int *new_j);

// Get neighbors down (right and below)
void getNeighborsDown(int A[][N], int i, int j, int *neighbors, int *count)
{
    *count = 0;
    if (j + 1 < N)
    {
        neighbors[(*count)++] = i * N + (j + 1);
    }
    if (i + 1 < N)
    {
        neighbors[(*count)++] = (i + 1) * N + j;
    }
}

// Move down
void moveDown(int A[][N], int i, int j, int *new_i, int *new_j)
{
    int neighbors[2], count, ni, nj, min_idx = -1;
    getNeighborsDown(A, i, j, neighbors, &count);
    if (count == 0)
    {
        *new_i = -1;
        *new_j = -1;
        return;
    }

    int min_val = A[i][j];
    for (int k = 0; k < count; k++)
    {
        ni = neighbors[k] / N;
        nj = neighbors[k] % N;
        if (A[ni][nj] < min_val)
        {
            min_val = A[ni][nj];
            min_idx = k;
        }
    }

    if (min_idx != -1)
    {
        ni = neighbors[min_idx] / N;
        nj = neighbors[min_idx] % N;
        int temp = A[i][j];
        A[i][j] = A[ni][nj];
        A[ni][nj] = temp;
        *new_i = ni;
        *new_j = nj;
    }
    else
    {
        *new_i = -1;
        *new_j = -1;
    }
}

// Pop minimum function
int popmin(int A[][N], int n)
{
    if (n == 0)
    {
        return -1; // No element to pop from an empty matrix
    }

    // The smallest element is at the top-left corner (0, 0)
    int retval = A[0][0];

    // Set the smallest element to INF
    A[0][0] = INF;

    // Start moving down from the top-left corner
    int ci = 0, cj = 0, new_i, new_j;
    moveDown(A, ci, cj, &new_i, &new_j);

    while (new_i != -1 && new_j != -1)
    {
        ci = new_i;
        cj = new_j;
        moveDown(A, ci, cj, &new_i, &new_j);
    }

    return retval;
}

// Main function for testing
int main()
{
    int A[N][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {10, 11, 12, 13, 14, 15, 16, 17, 18},
        {19, 20, 21, 22, 23, 24, 25, 26, 27},
        {28, 29, 30, 31, 32, 33, 34, 35, 36},
        {37, 38, 39, 40, 41, 42, 43, 44, 45},
        {46, 47, 48, 49, 50, 51, 52, 53, 54},
        {55, 56, 57, 58, 59, 60, 61, 62, 63},
        {64, 65, 66, 67, 68, 69, 70, 71, 72},
        {73, 74, 75, 76, 77, 78, 79, 80, INF}};

    int n = 9;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] == INF)
            {
                printf("INF ");
            }
            else
            {
                printf("%d ", A[i][j]);
            }
        }
        printf("\n");
    }

    int min_element = popmin(A, n);
    printf("\nPopped minimum element: %d\n", min_element);
    printf("Matrix after popmin operation:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] == INF)
            {
                printf("INF ");
            }
            else
            {
                printf("%d ", A[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}
