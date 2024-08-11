#include <stdio.h>
#include <limits.h>

#define MAX_DAYS 100

int maxportfolioValue(int prices[], int n);
int max(int a, int b);

// Calculates the maximum possible portfolio value given a list of stock prices and the number of days.
int main()
{
    int prices1[] = {3, 2, 6, 5};
    int n1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("Maximum portfolio value for test case 1: %d\n", maxportfolioValue(prices1, n1));

    int prices2[] = {1, 2, 3, 0, 2};
    int n2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("Maximum portfolio value for test case 2: %d\n", maxportfolioValue(prices2, n2));

    return 0;
}

/**
 * Calculates the maximum possible portfolio value given a list of stock prices and the number of days.
 *
 * @param prices An array of integers representing the stock prices for each day.
 * @param n The number of days.
 *
 * @return The maximum possible portfolio value. Returns -1 if the input is invalid.
 */
int maxportfolioValue(int prices[], int n)
{
    if (prices == NULL || n <= 0)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return -1;
    }

    int P_no_share[MAX_DAYS + 1] = {0};
    int P_one_share[MAX_DAYS + 1] = {INT_MIN};
    int P_sold_all[MAX_DAYS + 1] = {INT_MIN};

    // base case
    P_no_share[0] = 0;
    P_one_share[0] = INT_MIN;
    P_sold_all[0] = INT_MIN;

    for (size_t i = 1; i <= n; ++i)
    {
        if (i > MAX_DAYS)
        {
            fprintf(stderr, "Error: Input too large\n");
            return -1;
        }

        P_no_share[i] = max(P_no_share[i - 1], P_sold_all[i - 1]);
        P_one_share[i] = max(P_one_share[i - 1], P_no_share[i - 1] - prices[i - 1]);
        P_no_share[i] = (P_no_share[i - 1] > P_sold_all[i - 1]) ? P_no_share[i - 1] : P_sold_all[i - 1];
        P_one_share[i] = (P_one_share[i - 1] > P_no_share[i - 1] - prices[i - 1]) ? P_one_share[i - 1] : P_no_share[i - 1] - prices[i - 1];
        P_sold_all[i] = P_one_share[i - 1] + prices[i - 1];
    }

    return P_no_share[n];
}

/**
 * Returns the maximum of two integers.
 *
 * @param a The first integer to compare.
 * @param b The second integer to compare.
 *
 * @return The maximum of a and b.
 */
int max(int a, int b)
{
    return (a > b) ? a : b;
}
