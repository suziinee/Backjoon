N = int(input())
nums = []
for i in range(N) :
    nums.append(int(input()))

nums.sort()

cnt = {}
for n in nums :
    cnt[n] = nums.count(n)

max_cnt = max(cnt.values())
mcnt = [key for key, value in cnt.items() if value == max_cnt]
mcnt.sort()

print(int(round( sum(nums) / N, 0 )))
print(nums[len(nums)//2])
if len(mcnt) == 1 :
    print(mcnt[0])
else :
    print(mcnt[1])
print(max(nums) - min(nums))