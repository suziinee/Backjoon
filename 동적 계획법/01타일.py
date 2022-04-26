# dp[i] = dp[i-1] + dp[i-2]

N = int(input())

dp = {1 : 1, 2 : 2}

for i in range(3, N + 1) :
    if i in dp :
        continue
    else :
        dp[i] = (dp[i-2] + dp[i-1]) % 15746

print(dp[N])