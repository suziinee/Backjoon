# a(i) = max(k(i-1) + a(i-3) + k[i], a(i-2) + k[i])

n = int(input())
k = [0]
for i in range(n) :
    k.append(int(input()))

if n == 1 :
    print(k[1])
else :  
    dp = [0] * (n + 1)
    dp[1] = k[1]
    dp[2] = k[1] + k[2]

    for i in range(3, n + 1) :
        dp[i] = max(k[i-1] + dp[i-3] + k[i], dp[i-2] + k[i])

    print(dp[n])