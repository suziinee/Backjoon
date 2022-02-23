N = int(input())
M = int(input())

graph = [[] for i in range(N + 1)]
visited = [False] * (N + 1)

for i in range(M) :
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

res = []

def dfs(graph, v, visited) :
    visited[v] = True
    res.append(v)
    for i in graph[v] :
        if not visited[i] :
            dfs(graph, i, visited)

dfs(graph, 1, visited)

print(len(res) - 1)