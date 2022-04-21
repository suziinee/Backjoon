N = int(input())
road = list(map(int, input().split()))
cities = list(map(int, input().split()))

from collections import deque
road = deque(road)
cities = deque(cities)
ans = 0

tmp_city = cities.popleft()
tmp_road = 0

while cities :
    x = cities.popleft() #그 다음 city
    tmp_road += road.popleft()
    if tmp_city <= x :
        continue
    else :
        ans += (tmp_road) * tmp_city #현재까지의 거리에 요금 곱해서 ans에 더해주기
        tmp_road = 0 #거리 초기화
        tmp_city = x #city 갱신
ans += (tmp_road) * tmp_city

print(ans)

