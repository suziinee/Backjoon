class Deque:
    deque = []

    def push_front(self, x) :
        self.deque.insert(0, x)
    
    def push_back(self, x) :
        self.deque.append(x)
    
    def pop_front(self) :
        if self.deque :
            print(self.deque.pop(0))
        else :
            print(-1)
    
    def pop_back(self) :
        if self.deque :
            print(self.deque.pop())
        else :
            print(-1)
    
    def size(self) :
        print(len(self.deque))
    
    def empty(self) :
        if self.deque :
            print(0)
        else :
            print(1)
    
    def front(self) :
        if self.deque :
            print(self.deque[0])
        else :
            print(-1)
    
    def back(self) :
        if self.deque :
            print(self.deque[-1])
        else :
            print(-1)

Deque = Deque()
N = int(input())
import sys

for i in range(N) :
    command = sys.stdin.readline().split()
    if command[0] == "push_back" :
        Deque.push_back(command[1])
    elif command[0] == "push_front" :
        Deque.push_front(command[1])
    elif command[0] == "pop_front" :
        Deque.pop_front()
    elif command[0] == "pop_back" :
        Deque.pop_back()
    elif command[0] == "size" :
        Deque.size()
    elif command[0] == "empty" :
        Deque.empty()
    elif command[0] == "front" :
        Deque.front()
    elif command[0] == "back" :
        Deque.back()
    