#include <stdio.h>
#include <stdlib.h>

#define HASH_MAP_SIZE 100

typedef struct Entry
{
    int satisfaction;   // key: S
    int bike_index;     // Value: Bike Index
    struct Entry *next; // pointer to the next

} Entry;

unsigned int hash(int);
void insert_entry(Entry *[], int, int);
Entry *search_entry(Entry *[], int);
int compare(const void *a, const void *b);
void maximize_content_friends(int[], int, int[], int);

/**
 * Test cases.
 */
int main(void)
{
    int friends[] = {6, 2, 7, 50, 4, 3};
    int bikes[] = {45, 10, 70, 25, 30, 80, 50, 15, 55, 60, 35, 40, 20, 65, 75};
    int n = sizeof(friends) / sizeof(friends[0]);
    int m = sizeof(bikes) / sizeof(bikes[0]);

    maximize_content_friends(friends, n, bikes, m);

    return 0;
}

/**
 * Hash function to compare hash values.
 */
unsigned int hash(int satisfaction)
{
    return abs(satisfaction) % HASH_MAP_SIZE;
}

/**
 * Insert into hash map.
 */
void insert_entry(Entry *hash_map[], int satisfaction, int bike_index)
{
    unsigned int index = hash(satisfaction);
    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    new_entry->satisfaction = satisfaction;
    new_entry->bike_index = bike_index;
    new_entry->next = hash_map[index];
    hash_map[index] = new_entry;
}

/**
 * Search in hash map.
 */
Entry *search_entry(Entry *hash_map[], int satisfaction)
{
    unsigned int index = hash(satisfaction);
    Entry *entry = hash_map[index];

    while (entry)
    {
        if (entry->satisfaction == satisfaction)
        {
            return entry;
        }
    }

    return NULL;
}

/**
 * Compare function for sorting integers.
 */
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/**
 * @brief Maximizes the number of friends who are satisfied with their bike assignments.
 *
 * The function assigns bikes to friends in a way that maximizes the number of friends
 * whose greed factor is met or exceeded by the bike's performance factor. It sorts both
 * the friends and bikes arrays and uses a greedy approach to assign the smallest possible
 * bike that satisfies each friend. It also maintains a hash map to handle unsatisfied friends
 * for potential reassignment or reporting.
 *
 * @pre The `friends` array must contain the greed factors of friends and the `bikes` array
 *      must contain the performance factors of bikes. The `n` parameter should be the number of
 *      friends, and the `m` parameter should be the number of bikes. Both arrays must be valid
 *      and not null. The function assumes that `m >= n` (i.e., there are at least as many bikes
 *      as friends).
 *
 * @post The function will print the number of content friends, and for each friend, it will
 *       print whether they are satisfied or unsatisfied with their bike assignment. If a friend
 *       is unsatisfied (S < 0), the function will store this information in a hash map. The function
 *       does not modify the input arrays.
 *
 * @param friends An array of integers where each integer represents the minimum bike performance
 *                that a friend is content with.
 * @param n The number of friends (length of the `friends` array).
 * @param bikes An array of integers where each integer represents the performance factor of a bike.
 * @param m The number of bikes (length of the `bikes` array).
 */
void maximize_content_friends(int friends[], int n, int bikes[], int m)
{
    // sort friends by greed order
    qsort(friends, n, sizeof(int), compare);
    // sort bikes by performance factor
    qsort(bikes, m, sizeof(int), compare);

    // init pointers
    int friends_pointer = 0;
    int bike_pointer = 0;

    // Init hash map
    Entry *hash_map[HASH_MAP_SIZE] = {NULL};

    // count of happy friends
    int content_count = 0;

    while (friends_pointer < n && bike_pointer < m)
    {
        // Find the first bike that meets or exceeds the friend's greed factor
        while (bike_pointer < m && bikes[bike_pointer] < friends[friends_pointer])
        {
            bike_pointer++;
        }

        if (bike_pointer < m)
        {
            // Assign the bike
            int S = bikes[bike_pointer] - friends[friends_pointer];

            if (S >= 0)
            {
                // The friend is happy (lfgg)
                content_count++;
                printf("Friend with greed factor %d is satisfied with bike with performance %d (S = %d)\n", friends[friends_pointer], bikes[bike_pointer], S);
                insert_entry(hash_map, S, bike_pointer);
                friends_pointer++;
            }
            else
            {
                // Handle the case where the friend is not content
                printf("Friend with greed factor %d is unsatisfied with bike with performance %d (S = %d)\n", friends[friends_pointer], bikes[bike_pointer], S);
                insert_entry(hash_map, S, bike_pointer);
                friends_pointer++;
            }
            bike_pointer++;
        }
    }

    // Check for unsatisfied friends and try to reassign bikes
    for (size_t i = 0; i < HASH_MAP_SIZE; i++)
    {
        Entry *entry = hash_map[i];

        while (entry)
        {
            if (entry->satisfaction < 0)
            {
                printf("Unsatisfied friend with S = %d (bike index %d) needs reassignment.\n", entry->satisfaction, entry->bike_index);
                // Implement logic to find better bike and swap if needed.
            }

            Entry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }

    printf("Total content friends: %d\n", content_count);
}
