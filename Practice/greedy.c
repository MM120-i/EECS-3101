#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 100

void greedy_solution(int, int[], int, int[], int *);
void optimal_solution(int, int[], int, int[], int *);
int compare_solutions(int[], int, int[], int);

// Coin change problem.
int main(void)
{
    int coins[] = {100, 4, 3, 1};
    int amount = 6;
    int n = sizeof(coins) / sizeof(coins[0]);
    int greedy_result[SIZE], optimal_result[SIZE];
    int greedy_count, optimal_count;

    printf("Amount: %d\n", amount);
    printf("Coins: ");

    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", coins[i]);
    }
    printf("\n");

    greedy_solution(amount, coins, n, greedy_result, &greedy_count);
    optimal_solution(amount, coins, n, optimal_result, &optimal_count);

    printf("Greedy Solution: ");

    for (size_t i = 0; i < greedy_count; i++)
    {
        printf("%d ", greedy_result[i]);
    }

    printf("\nOptimal Solution: ");

    for (size_t i = 0; i < optimal_count; i++)
    {
        printf("%d ", optimal_result[i]);
    }

    printf("\n");

    if (compare_solutions(greedy_result, greedy_count, optimal_result, optimal_count))
    {
        printf("The greedy solution matches the optimal solution.\n");
    }
    else
    {
        printf("The greedy solution does not match the optimal solution.\n");
    }

    return 0;
}

/**
 * Finds greedy solution (solution taken from lecture).
 */
void greedy_solution(int amount, int coins[], int n, int result[], int *count)
{
    *count = 0; // counter for the number of coins.

    // Find the largest coin denomination that is less than or equal to the amount.
    while (amount > 0)
    {
        int found = 0;

        for (size_t i = 0; i < n; i++)
        {
            if (coins[i] <= amount)
            {
                amount -= coins[i];
                result[(*count)++] = coins[i];
                found = 1;
                break;
            }
        }

        // If no such coin is found
        if (!found)
        {
            printf("No greedy solution.\n");
            return;
        }
    }
}

/**
 * Finds the optimal solution using dynamic programming.
 */
void optimal_solution(int amount, int coins[], int n, int result[], int *count)
{
    int *dp = (int *)malloc((amount + 1) * sizeof(int));
    int *coin_used = (int *)malloc((amount + 1) * sizeof(int));

    // Initialize the dp array.
    for (size_t i = 0; i <= amount; i++)
    {
        dp[i] = INT_MAX;
        coin_used[i] = -1;
    }

    dp[0] = 0;

    // Compute the minimum coins needed for all values from 1 to 'amount'.
    for (size_t i = 1; i <= amount; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX)
            {
                if (dp[i] > dp[i - coins[j]] + 1)
                {
                    dp[i] = dp[i - coins[j]] + 1;
                    coin_used[i] = coins[j];
                }
            }
        }
    }

    if (dp[amount] == INT_MAX)
    {
        printf("No optimal solution.\n");
        free(dp);
        free(coin_used);
        return;
    }

    *count = 0;
    int temp_amount = amount;

    while (temp_amount > 0)
    {
        result[(*count)++] = coin_used[temp_amount];
        temp_amount -= coin_used[temp_amount];
    }

    free(dp);
    free(coin_used);
}

/**
 * Compares two solution (greedy and optimal).
 */
int compare_solutions(int result1[], int count1, int result2[], int count2)
{
    if (count1 != count2)
    {
        return 0;
    }

    for (size_t i = 0; i < count1; i++)
    {
        if (result1[i] != result2[i])
        {
            return 0;
        }
    }

    return 1;
}
