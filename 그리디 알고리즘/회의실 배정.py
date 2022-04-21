import sys
N = int(input())
times = []

for i in range(N) :
    times.append(list(map(int, sys.stdin.readline().split())))

# 끝나는 시간으로 정렬하되 끝나는 시간이 같으면 시작 시간으로 정렬
times = sorted(times, key = lambda x : (x[1], x[0]))

end = times[0][1]
cnt = 1
for i in range(1, N) :
    if times[i][0] >= end :
        cnt += 1
        end = times[i][1]

print(cnt)