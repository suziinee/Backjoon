import heapq
import sys

V, E = map(int, input().split())
start = int(input())
graph = [[] for i in range(V + 1)]

# a 정점에서 b로 가는 비용 c
for i in range(E) :
    a, b, c = map(int, sys.stdin.readline().split())
    graph[a].append((b, c))

# 최단거리 테이블
INF = int(1e9)
distance = [INF] * (V + 1)

def dijkstra(start) :
    q = []

    # 시작 노드를 거리를 0으로 해서 넣고 최단거리 테이블 갱신
    heapq.heappush(q, (0, start))
    distance[start] = 0

    # 알고리즘 시작
    while q :
        dist, now = heapq.heappop(q)

        # 만약 최단거리 테이블의 거리보다 클 경우는 무시
        if distance[now] < dist :
            continue
        
        # 그렇지 않을 경우는 그래프에서 인접 노드를 모두 꺼내서 비교
        for i in graph[now] :
            cost = dist + i[1]
            if cost < distance[i[0]] :
                distance[i[0]] = cost # 갱신 후
                heapq.heappush(q, (cost, i[0])) # heap에 넣어주기

dijkstra(start)

for i in range(len(distance)) :
    if i == 0 :
        continue
    if distance[i] == INF :
        print("INF")
    else :
        print(distance[i])