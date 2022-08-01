n = int(input())
arr = []
for i in range(n) :
  arr.append(list(map(int, input().split())))

ans = []

for a in arr :
  cnt = 0
  for b in arr :
    if a[0] < b[0] and a[1] < b[1] :
      cnt += 1
  cnt += 1
  ans.append(cnt)

print(*ans)