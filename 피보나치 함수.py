# dp[i] : i번째까지 1, 0 출력된 횟수
# dp[i] = dp[i-1] + dp[i-2]

T = int(input())

for t in range(T) :

    zero = {0 : 1, 1: 0, 2 : 1}
    one = {0 : 0, 1 : 1, 2 : 1}

    def fibo(n) :
        if n not in zero :
            for i in range(3, n + 1) :    
                zero[i] = zero[i-1] + zero[i-2]
                one[i] = one[i-1] + one[i-2]
        print(zero[n], one[n])
    
    fibo(int(input()))
                

