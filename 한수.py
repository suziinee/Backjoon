def h(n) :
    l = list(map(int, str(n)))
    if len(l) == 1 :
      return True
    d = l[0] - l[1]
    for i in range(len(l) - 1) :
        if l[i] - l[i+1] == d :
            continue
        return False
    return True

cnt = 0
N = int(input())
for i in range(1, N + 1) :
    if h(i) == True :
        cnt += 1

print(cnt) 