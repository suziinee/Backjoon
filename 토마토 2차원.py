import sys
from collections import deque 

M, N = map(int, input().split())
graph = []
for i in range(N) :
    graph.append(list(map(int, sys.stdin.readline().split())))
queue = deque()

dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

def bfs() :
    while queue :
        x, y = queue.popleft()
        for i in range(4) :
            nx = x + dx[i]
            ny = y + dy[i]
            if nx<0 or ny<0 or nx>=N or ny>=M :
                continue
            if graph[nx][ny] == 0 :
                graph[nx][ny] = graph[x][y] + 1
                queue.append((nx, ny))

for i in range(N) :
    for j in range(M) :
        if graph[i][j] == 1 :
            queue.append((i, j))

bfs()

res = -1
flag = 0
for i in range(N) :
    for j in range(M) :
        if graph[i][j] == 0 :
            flag = 1
        res = max(res, graph[i][j])

if flag == 1 :
    print(-1)
else :
    print(res - 1)
            
