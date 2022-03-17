N, K = map(int, input().split())

from collections import deque
queue = deque(list(range(1, N + 1)))
ans = []

while queue :
    for i in range(K) :
        x = queue.popleft()
        queue.append(x)
    ans.append(queue.pop())

res = '<'
for i in ans :
    res += str(i) 
    res += ', '
res = res[:-2]
res += '>'
print(res)