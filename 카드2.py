N = int(input())

from collections import deque
queue = deque(list(range(1, N + 1)))

while len(queue) != 1 :
    queue.popleft()
    x = queue.popleft()
    queue.append(x)

print(queue[0])