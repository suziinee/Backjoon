import sys
N = int(sys.stdin.readline())
nums = []
for i in range(N) :
    nums.append(int(sys.stdin.readline()))

nums.sort()
s = sum(nums)

cnt = {}
for n in nums :
    if n in cnt :
        cnt[n] += 1
    else :
        cnt[n] = 1

max_cnt = max(cnt.values())
mcnt = [key for key, value in cnt.items() if value == max_cnt]
mcnt.sort()

print(int(round( s / N, 0 )))
print(nums[N//2])
if len(mcnt) == 1 :
    print(mcnt[0])
else :
    print(mcnt[1])
print(max(nums) - min(nums))