N = int(input())

def mysum(n) :
    return sum(map(int, str(n))) + n 

for i in range(1, N) :
    if mysum(i) == N :
        print(i)
        break 
else :
    print(0)