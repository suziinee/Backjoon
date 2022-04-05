T = int(input())

a, b, c = 300, 60, 10
ans = [0] * 3

while T >= 10 :
    if T >= a :
        ans[0] += (T // a)
        T %= a
        continue
    elif T >= b :
        ans[1] += (T // b)
        T %= b 
        continue
    else :
        ans[2] += (T // c)
        T %= c 

if T :
    print(-1)
else :
    print(*ans)
