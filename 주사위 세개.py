nums = list(map(int, input().split()))

nums_set = set(nums)

if len(nums_set) == 1 :
    print(10000 + nums[0] * 1000)
elif len(nums_set) == 2 :
    for n in nums :
        if nums.count(n) == 2 :
            print(1000 + n * 100)
            break
else :
    nums.sort(reverse = True)
    print(nums[0] * 100)
