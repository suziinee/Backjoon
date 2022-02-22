N, M, V = map(int, input().split())

graph = [[] for i in range(N + 1)] #0번 노드는 사용하지 않음

for i in range(M) :
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

graph = [sorted(g) if g else [] for g in graph]

visited_d = [False] * (N+1)
visited_b = [False] * (N+1) 

def dfs(graph, V, visited_d) :
    visited_d[V] = True
    print(V, end = ' ')
    for i in graph[V] :
        if not visited_d[i] :
            dfs(graph, i, visited_d)

from collections import deque
def bfs(graph, V, visited_b) :
    q = deque([V])
    visited_b[V] = True
    while q :
        v = q.popleft()
        print(v, end = ' ')
        for i in graph[v] :
            if not visited_b[i] :
                q.append(i)
                visited_b[i] = True

dfs(graph, V, visited_d)
print()
bfs(graph, V, visited_b)
