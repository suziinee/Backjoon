from collections import deque

def balance(p_list) :
    d = {"(" : ")", "[" : "]"}
    stack = [p_list.popleft()]
    while p_list :
        x = p_list.popleft()
        if stack and (stack[-1] in d) and (d[stack[-1]] == x) :
            stack.pop()
        else :
            stack.append(x)
    
    if stack :
        print("no")
    else :
        print("yes")


while True :
    string = input()
    if string == "." :
        break
    
    p_list = []
    for s in string :
        if s == "(" or s == ")" or s == "[" or s == "]" :
            p_list.append(s)
    
    if p_list :
        p_list = deque(p_list)
        balance(p_list)
    else :
        print("yes")