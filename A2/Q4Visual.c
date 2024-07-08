#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_multiply_monotone();
long long multiply_monotone(const char *, const char *);

int main(void)
{
    test_multiply_monotone();
    return 0;
}

long long multiply_monotone(const char *x, const char *y)
{
    // Convert strings to long long
    long long xInt = atoll(x);
    long long yInt = atoll(y);

    // Base case: if yInt is single digit, perform direct multiplication
    if (strlen(x) == 1 || strlen(y) == 1)
    {
        return xInt * yInt;
    }

    // divide
    int mid = strlen(y) / 2;

    char prefix[20];
    strncpy(prefix, y, mid);
    prefix[mid] = '\0';

    long long suffix = multiply_monotone(x, prefix);

    char suffixString[40];
    sprintf(suffixString, "%lld", suffix);

    char prefix_str[40];
    sprintf(prefix_str, "%s", suffixString);

    for (int i = 0; i < mid; i++)
    {
        strcat(prefix_str, "0");
    }

    // Conquer
    long long prefixInt = atoll(prefix_str);

    return prefixInt + suffix;
}

void test_multiply_monotone()
{
    struct
    {
        const char *a;
        const char *b;
        long long expected;

    } test_cases[] = {

        {"5555", "7777", 43201235},
        {"3333", "2222", 7405926},
        {"4444", "1111", 4932834},
        {"9999", "9999", 99890001},
        {"1111", "1111", 1234321}};

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++)
    {

        long long result = multiply_monotone(test_cases[i].a, test_cases[i].b);

        printf("Test %d: multiply_monotone(%s, %s) = %lld\n",
               i + 1, test_cases[i].a, test_cases[i].b, result);
        printf("Expected: %lld\n\n", test_cases[i].expected);
    }
}
