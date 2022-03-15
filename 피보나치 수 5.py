n = int(input())

def pibonacci(n) :
    if n == 0 :
        return 0
    elif n == 1 :
        return 1
    else :
        return pibonacci(n - 1) + pibonacci(n - 2)

print(pibonacci(n))