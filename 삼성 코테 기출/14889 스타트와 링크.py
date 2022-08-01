from itertools import combinations
from collections import deque

N = int(input())
arr = [[] for _ in range(N)]
for i in range(N) :
  arr[i].extend(list(map(int, input().split())))

combs = deque(combinations(list(range(N)), N//2))
min_ = 100000

while combs :
  start = combs.popleft()
  start_score = 0
  link = combs.pop()
  link_score = 0

  for s in start :
    start_score += sum(arr[s]) - sum([arr[s][i] for i in link])

  for l in link :
    link_score += sum(arr[l]) - sum([arr[l][i] for i in start])
    
  if min_>abs(start_score - link_score) :
    min_ = abs(start_score - link_score)

print(min_)