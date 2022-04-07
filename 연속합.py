n = int(input())
nums = list(map(int, input().split()))
dp = [0] * n

# dp[i] : i번째까지 연속된 수의 최대 합
# dp[i] = max(nums[i] + dp[i-1], nums[i])

# 초기화
dp[0] = nums[0]

for i in range(1, n) :
    dp[i] = max(nums[i] + dp[i-1], nums[i])

print(dp)