#include <stdio.h>
#include <stdlib.h>

#define UNIT_SEGMENT_LENGTH 1.0
#define SIZE 5

int compare(const void *, const void *);
void markedPoints(double[], int);
void printArray(double[]);

int main(void)
{
    // test cases
    double points1[] = {0.5, 1.2, 2.4, 3.6, 3.8};
    int n1 = sizeof(points1) / sizeof(points1[0]);

    double points2[] = {1.0, 2.0, 3.0, 4.0};
    int n2 = sizeof(points2) / sizeof(points2[0]);

    double points3[] = {0.1, 0.2, 0.3, 0.4, 0.5};
    int n3 = sizeof(points3) / sizeof(points3[0]);

    double points4[] = {3.2, 1.3, 2.0, 1.1, 3.1};
    int n4 = sizeof(points4) / sizeof(points4[0]);

    printf("Test Case 1:\nFirst set: ");
    printArray(points1);
    markedPoints(points1, n1);
    printf("\n");

    printf("Test Case 2:\nSecond set: ");
    printArray(points2);
    markedPoints(points2, n2);
    printf("\n");

    printf("Test Case 3:\nThird set: ");
    printArray(points3);
    markedPoints(points3, n3);
    printf("\n");

    printf("Test case 4:\nFourth set: ");
    printArray(points4);
    markedPoints(points4, n4);
    printf("\n");

    return 0;
}

/**
 * Prints array.
 */
void printArray(double points[])
{
    for (size_t i = 0; i < SIZE; i++)
    {
        printf("%0.1f ", points[i]);
    }
    printf("\n");
}

/**
 * Comparator function for qSort to sort the points in ascending order.
 */
int compare(const void *a, const void *b)
{
    if (*(double *)a < *(double *)b)
    {
        return -1;
    }

    if (*(double *)a > *(double *)b)
    {
        return 1;
    }

    return 0;
}

/**
 * Finds the minimum number of unit-length intervals to cover all points.
 */
void markedPoints(double points[], int n)
{
    // Sort
    qsort(points, n, sizeof(double), compare);

    int S = n;
    int U = 0;
    int i = 0;

    if (S == 0)
    {
        printf("Empty input set.\n");
        return;
    }

    while (i < n)
    {
        U++; // Add a new interval
        double intervalStart = points[i];
        double intervalEnd = intervalStart + UNIT_SEGMENT_LENGTH;

        // Move to the next point that is not marked by this interval.
        while (i < n && points[i] <= intervalEnd)
        {
            i++;
        }

        if (U >= S)
        {
            printf("Failed to minimize segment usage.\n");
            return;
        }
    }

    printf("Total number of points (S): %d\n", S);
    printf("Total number of unit intervals (U): %d\n", U);
}
