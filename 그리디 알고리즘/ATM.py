N = int(input())
p = list(map(int, input().split()))
d = {}
p.sort()

sums = 0
for idx, time in enumerate(p) :
    sums += time 
    d[idx] = sums 

print(sum(d.values()))
