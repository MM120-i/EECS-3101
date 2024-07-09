#include <stdio.h>
#include <limits.h>

#define INF INT_MAX
#define N 9

// Function prototypes
void getNeighborsUp(int A[][N], int i, int j, int *neighbors, int *count);
void moveUp(int A[][N], int i, int j);
void getNeighborsDown(int A[][N], int i, int j, int *neighbors, int *count);
void moveDown(int A[][N], int i, int j);
void insert(int A[][N], int value);
int popmin(int A[][N]);
void sort(int A[][N], int n);
void printMatrix(int A[][N], int n);

int main()
{
    int A[N][N] = {
        {81, 79, 34, 65, 77, 80, 45, 55, 1},
        {42, 30, 11, 15, 28, 13, 23, 18, 49},
        {14, 51, 39, 60, INF, 3, 33, 6, 35},
        {66, 69, 70, 32, 20, 4, 75, 12, 40},
        {24, 31, 29, 67, 74, 36, 19, 72, 25},
        {76, 78, 21, 62, 44, 5, INF, 27, 10},
        {71, 2, 22, 50, 63, 7, 26, 46, 16},
        {53, 41, 48, 52, 68, 17, 8, 9, 37},
        {43, 73, 64, 59, 58, 38, 57, 56, 54}};

    int n = 9;

    printf("Matrix before sorting:\n");
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

    sort(A, n);
    printf("\nMatrix after sorting:\n");
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
void getNeighborsUp(int A[][N], int i, int j, int *neighbors, int *count)
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

// Move up in the matrix to maintain order
void moveUp(int A[][N], int i, int j)
{
    int neighbors[2], count, ni, nj;
    getNeighborsUp(A, i, j, neighbors, &count);

    int smallest = A[i][j];
    int smallest_i = i, smallest_j = j;

    for (int k = 0; k < count; k++)
    {
        ni = neighbors[k] / N;
        nj = neighbors[k] % N;
        if (A[ni][nj] > smallest)
        {
            smallest = A[ni][nj];
            smallest_i = ni;
            smallest_j = nj;
        }
    }

    if (smallest_i != i || smallest_j != j)
    {
        int temp = A[i][j];
        A[i][j] = A[smallest_i][smallest_j];
        A[smallest_i][smallest_j] = temp;
        moveUp(A, smallest_i, smallest_j);
    }
}

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

// Move down in the matrix to maintain order
void moveDown(int A[][N], int i, int j)
{
    int neighbors[2], count, ni, nj;
    getNeighborsDown(A, i, j, neighbors, &count);

    int smallest = A[i][j];
    int smallest_i = i, smallest_j = j;

    for (int k = 0; k < count; k++)
    {
        ni = neighbors[k] / N;
        nj = neighbors[k] % N;
        if (A[ni][nj] < smallest)
        {
            smallest = A[ni][nj];
            smallest_i = ni;
            smallest_j = nj;
        }
    }

    if (smallest_i != i || smallest_j != j)
    {
        int temp = A[i][j];
        A[i][j] = A[smallest_i][smallest_j];
        A[smallest_i][smallest_j] = temp;
        moveDown(A, smallest_i, smallest_j);
    }
}

// Insert value function
void insert(int A[][N], int value)
{
    A[N - 1][N - 1] = value;
    moveUp(A, N - 1, N - 1);
}

// Pop the smallest value from the matrix
int popmin(int A[][N])
{
    int retval = A[0][0];
    A[0][0] = INF;
    moveDown(A, 0, 0);
    return retval;
}

// Sort function
void sort(int A[][N], int n)
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
            insert(B, A[i][j]);
        }
    }

    // Extract sorted elements back into A
    for (int i = 0, k = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++, k++)
        {
            A[k / n][k % n] = popmin(B);
        }
    }
}
