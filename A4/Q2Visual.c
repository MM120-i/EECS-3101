#include <stdio.h>
#include <limits.h>

#define MAX_DAYS 100

int maxportfolioValue(int prices[], int n);

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

int maxportfolioValue(int prices[], int n)
{
    int P_no_share[MAX_DAYS + 1] = {0};
    int P_one_share[MAX_DAYS + 1] = {INT_MIN};
    int P_sold_all[MAX_DAYS + 1] = {INT_MIN};

    // base case
    P_no_share[0] = 0;
    P_one_share[0] = INT_MIN;
    P_sold_all[0] = INT_MIN;

    for (size_t i = 1; i <= n; ++i)
    {
        P_no_share[i] = (P_no_share[i - 1] > P_sold_all[i - 1]) ? P_no_share[i - 1] : P_sold_all[i - 1];
        P_one_share[i] = (P_one_share[i - 1] > P_no_share[i - 1] - prices[i - 1]) ? P_one_share[i - 1] : P_no_share[i - 1] - prices[i - 1];
        P_sold_all[i] = P_one_share[i - 1] + prices[i - 1];
    }

    return P_no_share[n];
}
