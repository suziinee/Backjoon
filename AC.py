import ast
import sys

T = int(input())
for i in range(T) :
    p = input()
    n = int(input())
    arr = ast.literal_eval(sys.stdin.readline())
    R = 0
    front, back = 0, 0

    for i in p :
        if i == "R" :
            R += 1
        elif i == "D" : 
            if R % 2 == 0 :
                front += 1
            else :
                back += 1
        
    if front + back <= n :
        arr = arr[front : n - back]
        if R % 2 == 0 :
            print(arr)
        else :
            print(arr[::-1])
    else :
        print("error")