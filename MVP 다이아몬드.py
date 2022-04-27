N = int(input())
nums = list(map(int, input().split()))
mvp = list(input())

d = {}
d['B'] = nums[0] - 1
d['S'] = nums[1] - 1
d['G'] = nums[2] - 1
d['P'] = nums[3] - 1
d['D'] = nums[3]

month = {x : 0 for x in range(N)}

for i in range(N) :
    if i == 0 :
        month[i] = d[mvp[i]]
    elif mvp[i] == 'D' :
        month[i] = d[mvp[i]]
    else :
        month[i] = d[mvp[i]] - month[i - 1]

print(sum(month.values()))