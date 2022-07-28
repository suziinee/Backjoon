N = int(input())
people = list(map(int, input().split()))
a, b = map(int, input().split())
res = 0

#총감독관이 일단 한명씩 전부 들어감
people = [p-a for p in people]
res += N

for p in people :
  if p>0 :
    if p%b==0 : 
      res += p//b
    else :
      res += (p//b + 1)

print(res)