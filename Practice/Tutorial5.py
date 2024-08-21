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

# Test case for q1:
loads = [5, 8, 10, 11, 9, 6, 7]
r = 10
w = 80
print(minLaundryCost(loads, r, w)) 


# Q2
def dataProcessed(x, s):

    n = len(x)
    Opt = [[0] * (n + 1) for _ in range(n + 1)] # dp table

    for j in range(1, n + 1):
        Opt[n][j] = min(x[n - 1], s[j - 1])
    
    for i in range(n - 1, 0, -1):

        for j in range(1, i + 1):
            reboot = Opt[i + 1][1]
            continueProcessing = min(x[i - 1], s[j - 1]) + Opt[i + 1][j + 1]
            Opt[i][j] = max(reboot, continueProcessing)

    return Opt[1][1]

# test case for q2:
x = [10, 1, 7, 7]
s = [8, 4, 2, 1]
print(dataProcessed(x, s))
