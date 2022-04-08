n = int(input())
graph = []
for i in range(n) :
    graph.append(list(map(int, input().split())))

# dp[i][j] = graph[i][j] + max(graph[i-1][j-1], graph[i-1][j])

dp = []
for i in range(n) :
    dp.append([])
    for j in range(i + 1) :
        dp[i].append(0)

for i in range(n) :
    for j in range(i + 1) :
        if i == 0 :
            dp[i][j] = graph[0][0]
            continue
        if j == 0 : left = 0
        else : left = dp[i-1][j-1]
        if j == i : right = 0
        else : right = dp[i-1][j]
        dp[i][j] = graph[i][j] + max(left, right)

print(max(dp[-1]))

        
    