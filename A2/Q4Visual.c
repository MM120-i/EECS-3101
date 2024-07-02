#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int char_to_int(char c)
{
    return c - '0';
}

long long multiply_monotone(const char *x, const char *y)
{
    int n = strlen(x);

    if (n != strlen(y))
    {
        fprintf(stderr, "Error: Input numbers must have equal length\n");
        exit(EXIT_FAILURE);
    }

    // Base case:
    if (n == 1)
    {
        return char_to_int(x[0]) * char_to_int(y[0]);
    }

    // Divide:
    int m = n / 2;
    char *x1 = (char *)malloc((m + 1) * sizeof(char));
    char *x2 = (char *)malloc((n - m + 1) * sizeof(char));
    char *y1 = (char *)malloc((m + 1) * sizeof(char));
    char *y2 = (char *)malloc((n - m + 1) * sizeof(char));

    if (!x1 || !x2 || !y1 || !y2)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    strncpy(x1, x, m);
    x1[m] = '\0';
    strncpy(x2, x + m, n - m);
    x2[n - m] = '\0';

    strncpy(y1, y, m);
    y1[m] = '\0';
    strncpy(y2, y + m, n - m);
    y2[n - m] = '\0';

    // Conquer:
    long long result1 = multiply_monotone(x1, y1);
    long long result2 = multiply_monotone(x2, y2);

    int sum1 = atoi(x1) + atoi(x2);
    int sum2 = atoi(y1) + atoi(y2);
    char sum1_str[20], sum2_str[20];
    snprintf(sum1_str, 20, "%d", sum1);
    snprintf(sum2_str, 20, "%d", sum2);

    long long result3 = multiply_monotone(sum1_str, sum2_str);

    free(x1);
    free(x2);
    free(y1);
    free(y2);

    // Combine:
    return result1 * pow(10, 2 * (n - m)) + (result3 - result1 - result2) * pow(10, n - m) + result2;
}

// Test cases
int main()
{
    const char *test1_x = "33";
    const char *test1_y = "33";
    printf("multiply_monotone(%s, %s) = %lld\n", test1_x, test1_y, multiply_monotone(test1_x, test1_y));

    const char *test2_x = "7777";
    const char *test2_y = "7777";
    printf("multiply_monotone(%s, %s) = %lld\n", test2_x, test2_y, multiply_monotone(test2_x, test2_y));

    const char *test3_x = "5555";
    const char *test3_y = "5555";
    printf("multiply_monotone(%s, %s) = %lld\n", test3_x, test3_y, multiply_monotone(test3_x, test3_y));

    // Unequal length case
    const char *test4_x = "555";
    const char *test4_y = "55";

    printf("multiply_monotone(%s, %s) = %lld\n", test4_x, test4_y, multiply_monotone(test4_x, test4_y));

    return 0;
}
