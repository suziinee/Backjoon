N = int(input())
l = []

for i in range(666, 2666800) :
    if '666' in str(i) :
        l.append(i)
    
l.sort()
print(l[N - 1])