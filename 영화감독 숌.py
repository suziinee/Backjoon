N = int(input())

l = [i for i in range(666, 2666800) if '666' in str(i)]
    
l.sort()
print(l[N - 1])