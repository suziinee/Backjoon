import sys
N = int(input())
nums = list(map(int, sys.stdin.readline().split()))
stack = []
ans = [-1 for i in range(N)]

for i in range(N) :
    while stack and nums[i] > nums[stack[-1]] :
        ans[stack.pop()] = nums[i]
    stack.append(i)

print(*ans)
