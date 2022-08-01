N = int(input())
arr = [[] for _ in range(N)]
for i in range(N) :
  arr[i].extend(list(map(int, input().split())))

nums = [i for i in range(N)]
combs = [[0] * (N//2), []]
min_ = 100000

def calcul(start, link) :
  start_score = 0
  link_score = 0
  for s in start :
    start_score += sum(arr[s]) - sum([arr[s][l] for l in link])
  for l in link :
    link_score += sum(arr[l]) - sum([arr[l][s] for s in start])
  return abs(start_score - link_score)

def dfs(L, BeginWith) :
  global min_
  if L == N//2 :
    for n in nums :
      if n not in combs[0] :
        combs[1].append(n)
    res = calcul(combs[0], combs[1])
    if res < min_ :
      min_ = res
    combs[1] = []    
  else :
    for i in range(BeginWith, N) :
      combs[0][L] = nums[i]
      dfs(L+1, i+1)

dfs(0, 0)
print(min_)