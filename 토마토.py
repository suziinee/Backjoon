import sys
from collections import deque

M, N, H = map(int, sys.stdin.readline().split())
graph = []

for h in range(H) :
    graph.append([])
    for n in range(N) :
        graph[h].append(list(map(int, sys.stdin.readline().split())))

dx = [1, -1, 0, 0, 0, 0] 
dy = [0, 0, -1, 0, 1, 0]
dz = [0, 0, 0, 1, 0, -1]
queue = deque()

def bfs() :
    while queue :
        x, y, z = queue.popleft()
        for i in range(6) :
            nx = x + dx[i]
            ny = y + dy[i]
            nz = z + dz[i]
            if nx<0 or ny<0 or nz<0 or nx>=H or ny>=N or nz>=M :
                continue 
            if graph[nx][ny][nz] == 0 :
                graph[nx][ny][nz] = graph[x][y][z] + 1
                queue.append((nx, ny, nz))
  
for i in range(H) :
    for j in range(N) :
        for k in range(M) :
            if graph[i][j][k] == 1 :
                queue.append((i, j, k))

bfs()

res = -2
flag = 0 
for i in range(H) :
    for j in range(N) :
        for k in range(M) :
            if graph[i][j][k] == 0 :
                flag = 1
            res = max(res, graph[i][j][k])

if flag == 1 :
    print(-1)
else :
    print(res - 1)





