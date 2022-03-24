class Queue:
    from collections import deque
    queue = deque()

    def push(self, x) :
        self.queue.append(x)
    
    def pop(self) :
        if self.queue :
            print(self.queue.popleft())
        else :
            print(-1)
    
    def size(self) :
        print(len(self.queue))
    
    def empty(self) :
        if self.queue :
            print(0)
        else :
            print(1)

    def front(self) :
        if self.queue :
            print(self.queue[0])
        else :
            print(-1)
    
    def back(self) :
        if self.queue :
            print(self.queue[-1])
        else :
            print(-1)

queue = Queue()
N = int(input())
import sys

for i in range(N) :
    nums = sys.stdin.readline().split()
    if len(nums) == 2 :
        queue.push(int(nums[1]))
    elif nums[0] == "pop" :
        queue.pop()
    elif nums[0] == "size" :
        queue.size()
    elif nums[0] == "empty" :
        queue.empty()
    elif nums[0] == "front" :
        queue.front()
    elif nums[0] == "back" :
        queue.back()