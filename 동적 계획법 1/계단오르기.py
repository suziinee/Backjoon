# a(i) = max(k(i-1) + a(i-3) + k[i], a(i-2) + k[i])

n = int(input())
k = [0]
for i in range(n) :
    k.append(int(input()))

dp = [0] * (n + 1) 
dp[1] = k[1]
dp[2] = k[1] + k[2]

if n == 1 :
    print(d[1])
else :
    for i in range(3, n + 1) :
        dp[i] = max(k[i-1] + a[i-3] + k[i], a[i-2] + k[i])
    print(dp[n])