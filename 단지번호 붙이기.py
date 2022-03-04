N = int(input())
graph = []
ans = []

for i in range(N) :
    graph.append(list(map(int, input())))

cnt = 0

def dfs(x, y) :
    global cnt
  
    if x < 0 or y < 0 or x >= N or y >= N :
        return False

    if graph[x][y] == 1 :
        graph[x][y] = 0 #방문처리
        cnt += 1
        dfs(x-1, y)
        dfs(x+1, y)
        dfs(x, y-1)
        dfs(x, y+1)
        return True        
    
    return False
        

for i in range(N) :
    for j in range(N) :
        if dfs(i, j) :
            ans.append(cnt)
            cnt = 0

ans.sort()
print(len(ans))
for i in ans :
    print(i)