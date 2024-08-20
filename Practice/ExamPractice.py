# WEEK 1

def avg(A):
    """PRE: A is a list of numbers."""
    """POST: The average of the numbers in A"""

    sum = 0
    i = 0

    while i < len(A):

        sum += A[i]
        i += 1
    
    return sum / len(A)

def is_prime(n):
    """PRE: n is a natural number, n >= 2"""
    """POST: True if n is a prime number, False otherwise"""

    m = 2
    result = True
    k = m - 1

    while m <= n/2:

        if n % m == 0:
            result = False
        m += 1

    return result

def compute_gcd(x, y):
    """PRE: x, y: positve natural numbers"""
    """POST: The greatest common divisor of x and y"""

    a = x
    b = y
    
    while a != b:

        V = a + b   # Variant

        if a > b:
            a = a - b
        else:
            b = b - a

    return a

def compute_lcm(x, y):
    """PRE: x, y: positve natural numbers"""
    """POST: The least common multiple of x and y"""

    return (x * y) / compute_gcd(x, y)

def MULT3(m, n):
    # Precondition: m is a natural number (m ∈ N) and n is an integer (n ∈ Z)

    x = m
    y = n
    z = 0
    
    while x != 0:

        if x % 3 == 1:
            z += y
            x //= 3
        elif x % 3 == 0:
            x //= 3
        else:
            z -= y
            x = (x + 1) // 3

        y *= 3
    
    return z

def myTest(n):

    if n <= 0:
        return 0
    else:
        i = random(n - 1)
        return myTest(i) + myTest(n - 1 - i)


# WEEK 3

def max_crossing(A, low, mid, high):

    leftSum = 0
    s = 0

    for i in range(mid, low - 1, -1):
        s = s + A[i]

        if s > leftSum:
            leftSum = s
    
    rightSum = 0
    s = 0

    for i in range(mid + 1, high + 1):
        s = s + A[i]

        if s > rightSum:
            rightSum = s

    return leftSum + rightSum



def max_seg_sum(A, low, high):
    
    if low == high:
        return max(A[low], 0)
    
    mid = (low + high) // 2
    leftSum = max_seg_sum(A, low, mid)
    rightSum = max_seg_sum(A, mid + 1, high)
    crossSum = max_crossing(A, low, mid, high)
    
    return max(leftSum, rightSum, crossSum)


# Tests:
numbers = [1, 2, 3, 4, 5]
print("The average of", numbers, "is", avg(numbers)) # Avg fuction
print(is_prime(11)) # Prime function
print(compute_lcm(15, 10))
print(MULT3(5, 10))
arr = [2, -5, 8, -6, 10, -2]
print(max_seg_sum(arr, arr[0], arr[len(arr)-1]))
    
