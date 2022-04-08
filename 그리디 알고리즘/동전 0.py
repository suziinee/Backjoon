n, k = map(int, input().split())
coins = []
for i in range(n) :
    coins.append(int(input()))

from collections import deque
coins = deque(coins)

ans = 0

for i in range(n) :
    x = coins.pop()
    if k >= x :
        ans += (k // x)
        k %= x 
    continue

print(ans)