# dp[i] : i번째까지 마실 수 있는 최대 포도주의 양
# dp[i] = max(dp[i-3] + k[i-1] + k[i], dp[i-2] + k[i], dp[i-1]) (i >= 3)

import sys
n = int(input())
nums = [0]
for i in range(n) :
    nums.append(int(sys.stdin.readline()))

# dp 초기화
dp = [0] * (n + 1)
if n == 1 :
    print(nums[1])
else :
    dp[1] = nums[1]
    dp[2] = nums[1] + nums[2]

    for i in range(3, n + 1) :
        dp[i] = max(dp[i-3] + nums[i-1] + nums[i], dp[i-2] + nums[i], dp[i-1])

    print(max(dp))