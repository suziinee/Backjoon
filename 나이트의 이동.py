T = int(input())

for t in range(T) :

    N = int(input())
    start = list(map(int, input().split()))
    end = list(map(int, input().split()))

    dx = [-2, -1, 1, 2, 2, 1, -1, -2]
    dy = [1, 2, 2, 1, -1, -2, -2, -1]

    # 리스트를 전부 0(방문 안함)으로 채워넣기
    graph = []
    for i in range(N) :
        graph.append([0] * N)

    from collections import deque
    def bfs(x, y) :
        global end
        queue = deque()
        queue.append((x, y))
        while queue :
            x, y = queue.popleft()
            if x == end[0] and y == end[1] :
                break
            for i in range(8) :
                nx = x + dx[i]
                ny = y + dy[i]
                if nx >= N or ny >= N or nx < 0 or ny < 0 :
                    continue
                if graph[nx][ny] == 0 :
                    graph[nx][ny] = graph[x][y] + 1
                    queue.append((nx, ny))
        print(graph[end[0]][end[1]])

    bfs(start[0], start[1])