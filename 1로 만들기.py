# dp[i] : i를 1로 만들기 위한 최소 횟수
# dp[i] = min(dp[i] vs dp[i-1], dp[i//2], dp[i//3] + 1)

N = int(input())
dp = [0] * (N + 1) 

# 초기화
# dp[0]은 사용하지 않음 / dp[1] = 0

for i in range(2, N + 1) :
    dp[i] = dp[i-1] + 1
    if i % 3 == 0 :
        dp[i] = min(dp[i], dp[i//3] + 1) 
    if i % 2 == 0 :
        dp[i] = min(dp[i], dp[i//2] + 1) 

print(dp[N])