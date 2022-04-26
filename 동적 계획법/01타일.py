from itertools import combinations as comb
N = int(input())

if N % 2 == 0 :
    zero = N
else :
    zero = N - 1

ans = 0
for i in range(0, zero + 1, 2) :
    if i == 0 :
        ans += 1
    else :
        ans += len(list(comb(range((N - i) + (i//2)), i//2)))

print(ans % 15746)
