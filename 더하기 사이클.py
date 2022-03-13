def new(n) :
    s = sum(map(int, str(n)))
    return int(str(n)[-1] + str(s)[-1])

num = 1
cnt = 0
while num :
    if cnt == 0 :
        N = int(input())
        if N == 0 :
          print(1)
          break
        else :
          num = new(N)
          cnt += 1
    else :
        num = new(num)
        cnt += 1
        if num == N :
            print(cnt)
            break
        
