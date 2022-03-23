K = int(input())
stack = []

for i in range(K) :
    x = input()
    if x == "0" :
        stack.pop()
    else :
        stack.append(x)

print(sum(list(map(int, stack))))