N = int(input())
people = []
rank = []
for i in range(N) :
    x, y = map(int, input().split())
    people.append((x, y))

for p in people :
    cnt = 0
    for j in people :
        if p[0] < j[0] and p[1] < j[1] :
            cnt += 1
    rank.append(cnt + 1)

for r in rank :
    print(r, end = ' ')