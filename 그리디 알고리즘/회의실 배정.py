N = int(input())
times = []
ans = []
from bisect import bisect_left

for i in range(N) :
    times.append(list(map(int, input().split())))

# 시작시간으로 정렬
times = sorted(times, key = lambda x : x[0])
start_time = [x[0] for x in times]
end_time = [x[1] for x in times]

# 가장 첫 시작시간의 끝시간보다 시작시간이 큰 구간은 탐색하지 않아도 됨
border = bisect_left(start_time, end_time[0])

for i in range(border) :
    end = end_time[i]
    res = 1
    while end <= start_time[-1] : #더이상 시작할 수 없을때까지 반복
        res += 1
        next_ = bisect_left(start_time, end) #다음 시작시간 index
        end = end_time[next_]
    ans.append(res)

print(max(ans))