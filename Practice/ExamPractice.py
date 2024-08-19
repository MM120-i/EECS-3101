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


# Tests:
numbers = [1, 2, 3, 4, 5]
print("The average of", numbers, "is", avg(numbers)) # Avg fuction
print(is_prime(11)) # Prime function
print(compute_lcm(15, 10))
print(MULT3(5, 10))
    
