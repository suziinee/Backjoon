nums = []

while True :
    n = int(input())
    if n != 0 :
        nums.append(n)
    else :
        break 

import math
for n in nums :
    n = list(str(n))[::-1]
    ans = 0
    for i in range(len(n)) :
        ans += int(n[i]) * math.factorial(i + 1)
    print(ans)
