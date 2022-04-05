# a(i) = max(a(i-1) + k(i), a(i-2) + k(i))

n = int(input())
k = []
for i in range(n) :
    k.append(int(input()))

dp = [0] * n 
dp[0] = k[0]
dp[1] = k[0] + k[1]
cnt = 1

for i in range(2, n) :
    if cnt == 1 :
        dp[i] = dp[i-2] + k[i]
        cnt = 0
    else :
        dp[i] = max(dp[i-1] + k[i], dp[i-2] + k[i])
        if dp[i] == dp[i-1] + k[i] :
            cnt += 1

print(dp[n-1])