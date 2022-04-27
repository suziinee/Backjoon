from itertools import permutations as perm
from collections import deque

N = int(input())
nums = input().split() #eval을 위해 str으로 받기
operators = list(map(int, input().split()))
d = {0 : "+", 1 : "-", 2 : "*", 3 : "/"}
new_op = []

for i in range(4) :
    new_op.extend([d[i]] * operators[i])

perms = list(set(perm(new_op, len(new_op))))

ans = []
n = len(new_op)
for op in perms :
    eval_ = deque(nums.copy())
    res = eval_.popleft()
    for i in range(n) :
        if op[i] == "/" :
            if int(res) < 0 :
                res = -(abs(int(res)) // int(eval_.popleft()))
            else :
                res = int(res) // int(eval_.popleft())
        else :
            res += op[i]
            res += eval_.popleft()
            res = eval(res)
        res = str(res)
    ans.append(int(res))

print(max(ans))
print(min(ans))

