def left(queue) :
    x = queue.popleft()
    queue.append(x)
    return queue

def right(queue) :
    x = queue.pop()
    queue.appendleft(x)
    return queue


N, M = map(int, input().split())
nums = list(map(int, input().split()))
cnt = 0

from collections import deque
queue = deque(list(range(1, N + 1)))

while len(queue) != N-M :
    if queue[0] == nums[0] :
        queue.popleft()
        nums.pop(0)
    else :
        idx = queue.index(nums[0])
        if idx <= (len(queue) // 2) :
            queue = left(queue)
            cnt += 1
        else :
            queue = right(queue)
            cnt += 1

print(cnt)
    
