class Stack:

    stack = []

    def push(self, X) :
        self.stack.append(X)
    def pop(self) :
        if self.stack : print(self.stack.pop())
        else : print(-1)
    def size(self) :
        print(len(self.stack))
    def empty(self) :
        if self.stack : print(0)
        else : print(1)
    def top(self) :
        if self.stack : print(self.stack[-1])
        else : print(-1)

S = Stack()
N = int(input())
import sys

for i in range(N) :
    cmd = sys.stdin.readline().split()
    if len(cmd) == 2 :
        S.push(int(cmd[1]))
    elif cmd[0] == "pop" :
        S.pop()
    elif cmd[0] == "size" :
        S.size()
    elif cmd[0] == "empty" :
        S.empty()
    elif cmd[0] == "top" :
        S.top()