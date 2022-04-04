T = int(input())

def vps(string) :
    dct = {"(" : ")"}
    from collections import deque
    string = deque(string)
    now = string.popleft()
    s = [now]
    while string :
        now = string.popleft()
        if s :
            if (s[-1] in dct) and (now == dct[s[-1]]) :
                s.pop()
            else :
                s.append(now)
        else :
            s.append(now)
    
    if s :
        print("NO")
    else :
        print("YES")

for i in range(T) :
    string = input()
    vps(string)
