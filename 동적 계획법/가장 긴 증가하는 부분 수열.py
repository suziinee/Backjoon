N = int(input())
nums = list(map(int, input().split()))

dp = [1] * N 

for i in range(N) :
    for j in range(0, i) :
        if nums[j] < nums[i] :
            dp[i] = max(dp[i], dp[j] + 1)

print(max(dp))
