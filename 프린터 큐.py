from collections import deque
T = int(input())

for t in range(T) :
    N, M = map(int, input().split())
    lst = list(map(int, input().split()))
    dic = {i : v for i, v in enumerate(lst)}
    queue = deque([i for i in range(len(lst))])
    ans = []

    while queue :
        x = queue.popleft()
        if any(dic[x] < dic[i] for i in queue) :
            queue.append(x)
        else :
            ans.append(x)
    
    print(ans.index(M) + 1)