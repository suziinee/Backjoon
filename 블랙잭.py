N, M = map(int, input().split())
nums = list(map(int, input().split()))

from itertools import combinations as c

combs = list(c(nums, 3))
combs = [sum(comb) for comb in combs if sum(comb) <= M]
print(max(combs))