def d(n) :
    ans = n + sum(map(int, str(n)))
    return ans 

l = list(range(1, 10001))

for i in range(1, 10001) :
    if d(i) in l :
        l.remove(d(i))

for i in l :
    print(i)
