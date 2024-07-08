def popmin(A, n):

    if n == 0:
        return None  # No element to pop from an empty matrix
    
    # The smallest element is at the top-left corner (0, 0)
    min_element = A[0][0]
    
    # Replace the smallest element with the bottom-right corner element
    A[0][0] = A[n-1][n-1]
    A[n-1][n-1] = float('inf')
    
    # Recursive function to maintain the properties
    def percolate_down(A, i, j, n):
        min_i, min_j = i, j
        
        # Check the right neighbor
        if j + 1 < n and A[i][j + 1] < A[min_i][min_j]:
            min_i, min_j = i, j + 1
        
        # Check the bottom neighbor
        if i + 1 < n and A[i + 1][j] < A[min_i][min_j]:
            min_i, min_j = i + 1, j
        
        # If the current element is not the smallest, swap and continue percolating down
        if (min_i, min_j) != (i, j):
            A[i][j], A[min_i][min_j] = A[min_i][min_j], A[i][j]
            percolate_down(A, min_i, min_j, n)
    
    # Start percolating down from the top-left corner
    percolate_down(A, 0, 0, n)
    
    return min_element

# # Example usage
A = [
    [2, 3, 4, 5],
    [8, 9, 12, 14],
    [16, float('inf'), float('inf'), float('inf')],
    [float('inf'), float('inf'), float('inf'), float('inf')]
]

for row in A:
    print(row)

print("\n")

n = 4
min_element = popmin(A, n)
print("Popped minimum element:", min_element)
print("Matrix after popmin operation:")

for row in A:
    print(row)

print("\n")

# Example usage with a 9x9 matrix
A = [
    [1, 2, 3, 4, 5, 6, 7, 8, 9],
    [10, 11, 12, 13, 14, 15, 16, 17, 18],
    [19, 20, 21, 22, 23, 24, 25, 26, 27],
    [28, 29, 30, 31, 32, 33, 34, 35, 36],
    [37, 38, 39, 40, 41, 42, 43, 44, 45],
    [46, 47, 48, 49, 50, 51, 52, 53, 54],
    [55, 56, 57, 58, 59, 60, 61, 62, 63],
    [64, 65, 66, 67, 68, 69, 70, 71, 72],
    [73, 74, 75, 76, 77, 78, 79, 80, float('inf')]
]

print("Before pop-min matrix")

for row in A:
    print(row)

print("\n")

n = 9
min_element = popmin(A, n)
print("Popped minimum element:", min_element)
print("Matrix after popmin operation:")

for row in A:
    print(row)
