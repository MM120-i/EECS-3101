# Q1
def minLaundryCost(loads, r, w):

    n = len(loads)
    OPT = [0] * (n + 1)

    for i in range(1, n + 1):

        costL1 = r * loads[i - 1] + OPT[i - 1]

        if i >= 3:
            costL2 = r * w + OPT[i - 3]
            OPT[i] = min(costL1, costL2)
        else:
            OPT[i] = costL1
    
    return OPT[n]

# Test case:
loads = [5, 8, 10, 11, 9, 6, 7]
r = 10
w = 80
print(minLaundryCost(loads, r, w)) 
