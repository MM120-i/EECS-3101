// HAS ORIGINAL VALUES

#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define N 9

// Function prototypes
void percolateUpward(int A[][N], int i, int j, int *neighbors, int *count);
void adjustUpward(int A[][N], int i, int j, int *new_i, int *new_j);
void percolateDownward(int A[][N], int i, int j, int *neighbors, int *count);
void adjustDownward(int A[][N], int i, int j, int *new_i, int *new_j);
int popmin(int A[][N]);
void insert(int A[][N], int value);
void swap(int A[][N], int i1, int j1, int i2, int j2);
void sort(int A[][N], int n);
void printMatrix(int A[][N], int n);

// Get neighbors up (left and above)
void percolateUpward(int A[][N], int i, int j, int *neighbors, int *count)
{
    *count = 0;
    if (j - 1 >= 0)
    {
        neighbors[(*count)++] = i * N + (j - 1);
    }
    if (i - 1 >= 0)
    {
        neighbors[(*count)++] = (i - 1) * N + j;
    }
}

// Get neighbors down (right and below)
void percolateDownward(int A[][N], int i, int j, int *neighbors, int *count)
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

// Move up
void adjustUpward(int A[][N], int i, int j, int *new_i, int *new_j)
{
    int neighbors[2], count, ni, nj, min_idx = -1;
    percolateUpward(A, i, j, neighbors, &count);

    if (count == 0)
    {
        *new_i = -1;
        *new_j = -1;
        return;
    }

    int min_val = INF;

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

    if (min_idx != -1 && A[i][j] < min_val)
    {
        ni = neighbors[min_idx] / N;
        nj = neighbors[min_idx] % N;

        swap(A, i, j, ni, nj);

        *new_i = ni;
        *new_j = nj;
    }
    else
    {
        *new_i = -1;
        *new_j = -1;
    }
}

// Move down
void adjustDownward(int A[][N], int i, int j, int *new_i, int *new_j)
{
    int neighbors[2], count, ni, nj, min_idx = -1;
    percolateDownward(A, i, j, neighbors, &count);

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

        swap(A, i, j, ni, nj);

        *new_i = ni;
        *new_j = nj;
    }
    else
    {
        *new_i = -1;
        *new_j = -1;
    }
}

// Swap two elements
void swap(int A[][N], int i1, int j1, int i2, int j2)
{
    int temp = A[i1][j1];
    A[i1][j1] = A[i2][j2];
    A[i2][j2] = temp;
}

// Pop minimum function
int popmin(int A[][N])
{
    // The smallest element is at the top-left corner (0, 0)
    int retval = A[0][0];

    // Set the smallest element to INF
    A[0][0] = INF;

    // Start moving down from the top-left corner
    int ci = 0, cj = 0, new_i, new_j;
    adjustDownward(A, ci, cj, &new_i, &new_j);

    while (new_i != -1 && new_j != -1)
    {
        ci = new_i;
        cj = new_j;
        adjustDownward(A, ci, cj, &new_i, &new_j);
    }

    return retval;
}

// Insert value function
void insert(int A[][N], int value)
{
    // Place the value in the bottom-right corner
    A[N - 1][N - 1] = value;

    // Start moving up from the bottom-right corner
    int ci = N - 1, cj = N - 1, new_i, new_j;
    adjustUpward(A, ci, cj, &new_i, &new_j);

    while (new_i != -1 && new_j != -1)
    {
        ci = new_i;
        cj = new_j;
        adjustUpward(A, ci, cj, &new_i, &new_j);
    }
}

// Sort function
void sort(int A[][N], int n)
{
    // Iterate over each element to ensure it's placed in the sorted order
    for (int i = 0; i < n * n; i++)
    {
        int min_val = popmin(A);
        insert(A, min_val);
    }
}

// Main function for testing
int main()
{
    int A[N][N] = {
        {81, 79, 34, 65, 77, 80, 45, 55, 1},
        {42, 30, 11, 15, 28, 13, 23, 18, 49},
        {14, 51, 39, 60, 61, 3, 33, 6, 35},
        {66, 69, 70, 32, 20, 4, 75, 12, 40},
        {24, 31, 29, 67, 74, 36, 19, 72, 25},
        {76, 78, 21, 62, 44, 5, 47, 27, 10},
        {71, 2, 22, 50, 63, 7, 26, 46, 16},
        {53, 41, 48, 52, 68, 17, 8, 9, 37},
        {43, 73, 64, 59, 58, 38, 57, 56, 54}};

    int n = 9;

    printf("Matrix before sorting:\n");
    printMatrix(A, n);

    sort(A, n);

    printf("\nMatrix after sorting:\n");
    printMatrix(A, n);

    return 0;
}

void printMatrix(int A[][N], int n)
{
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
}
