# dp[i][0]는 i집을 0번 color로 칠했을 때 최솟값
# dp[i][0] = graph[i][0] + min(dp[i-1][1], dp[i-1][2])

n = int(input())
graph = []
dp = []
for i in range(n) :
    graph.append(list(map(int, input().split())))
    dp.append([0, 0, 0])

# 초기값 설정
dp[0] = [graph[0][0], graph[0][1], graph[0][2]]

for i in range(1, n) :
    dp[i][0] = graph[i][0] + min(dp[i-1][1], dp[i-1][2])
    dp[i][1] = graph[i][1] + min(dp[i-1][0], dp[i-1][2])
    dp[i][2] = graph[i][2] + min(dp[i-1][0], dp[i-1][1])

print(min(dp[-1]))
    
