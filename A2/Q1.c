// CONTAINS ORIGINAL VARIABLE!

#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define N 9

// Helper functions:
void percolateDownward(int A[][N], int i, int j, int *neighbors, int *count);
void adjustDownward(int A[][N], int i, int j, int *new_i, int *new_j);
void adjustUpward(int A[][N], int i, int j, int *new_i, int *new_j);
void percolateUpward(int A[][N], int i, int j, int *neighbors, int *count);

// Other
void printMatrix(int A[][N], int n);
void sortAlt(int A[][N], int n);
void swap(int A[][N], int i, int j, int ni, int nj);

// Parts of the questions (a, b, c)
void insert(int A[][N], int n, int value); // Part B
void sort(int A[], int n);                 // Part C
int popmin(int A[][N], int n);             // Part A

// Main function for testing
int main(void)
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

    const int n = 9;

    printf("Matrix before insertion:\n");
    printMatrix(A, n);

    const int value_to_insert = 100;
    insert(A, n, value_to_insert);

    printf("\nMatrix after insertion of %d:\n", value_to_insert);
    printMatrix(A, n);

    printf("\n");
    const int x = popmin(A, n);

    printf("After popmin. Popped %d\n", x);
    printMatrix(A, n);

    printf("\nMatrix after sorting:\n");
    sort(A, n);
    // sortAlt(A, n);
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
    adjustDownward(A, ci, cj, &new_i, &new_j);

    for (; new_i != -1 && new_j != -1; adjustDownward(A, ci, cj, &new_i, &new_j))
    {
        ci = new_i;
        cj = new_j;
    }

    return retval;
}

// Insert value function
void insert(int A[][N], int n, int value)
{
    if (n == 0)
    {
        return; // Can't insert into an empty matrix
    }

    // Place the value in the bottom-right corner
    A[n - 1][n - 1] = value;

    // Start moving up from the bottom-right corner
    int ci = n - 1, cj = n - 1, new_i, new_j;
    adjustUpward(A, ci, cj, &new_i, &new_j);

    while (new_i != -1 && new_j != -1)
    {
        ci = new_i;
        cj = new_j;
        adjustUpward(A, ci, cj, &new_i, &new_j);
    }
}

// Sorting algorithm
void sort(int A[], int n)
{
    int B[N][N];

    // Initialize B with INF
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[i][j] = INF;
        }
    }

    // Insert elements from A into B
    for (int i = 0; i < n * n; i++)
    {
        insert(B, n, A[i]);
    }

    // Extract sorted elements back into A
    for (int i = 0; i < n * n; i++)
    {
        A[i] = popmin(B, n);
    }
}

// Alternative Sorting algorithm
void sortAlt(int A[][N], int n)
{
    int B[N][N];

    // Initialize B with INF values
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[i][j] = INF;
        }
    }

    // Insert all elements from A into B
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            insert(B, n, A[i][j]);
        }
    }

    // Extract sorted elements back into A
    for (int i = 0, k = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++, k++)
        {
            A[k / n][k % n] = popmin(B, n);
        }
    }
}

void swap(int A[][N], int i, int j, int ni, int nj)
{
    int temp = A[i][j];
    A[i][j] = A[ni][nj];
    A[ni][nj] = temp;
}
