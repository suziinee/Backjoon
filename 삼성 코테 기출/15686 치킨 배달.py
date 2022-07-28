from itertools import combinations
from collections import deque

n, m = map(int, input().split())
arr = []
house = []
chicken = []

for i in range(n) :
    arr.append(list(map(int, input().split())))
    for j in range(n) :
        if arr[i][j] == 1 :
            house.append((i, j))
        elif arr[i][j] == 2 :
            chicken.append((i, j))

# i번째 집의 j번째 치킨집과의 거리
distance = [[] for _ in range(len(house))]

for i in range(len(house)) :
    for j in range(len(chicken)) :
        distance[i].append(abs(house[i][0] - chicken[j][0]) + abs(house[i][1] - chicken[j][1]))
    
combs = deque(combinations(list(range(len(chicken))), m))
min_ = 1e9

def find_min(lst, idx) :
    min_ = 1e9
    for i in idx :
        if lst[i] < min_ : 
            min_ = lst[i]
    return min_

while combs :
    tmp = 0
    c = combs.popleft()
    for i in range(len(house)) :
        tmp += find_min(distance[i], c)
    if tmp < min_ :
        min_ = tmp

print(min_)