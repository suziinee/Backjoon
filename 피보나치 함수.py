# dp[i] : i번째까지 1, 0 출력된 횟수
# dp[i] = dp[i-1] + dp[i-2]

T = int(input())

for t in range(T) :

    zero = [1, 0, 1]
    one = [0, 1, 1]

    def fibo(n) :
        length = len(zero)
        if n >= length :
            for i in range(length, n + 1) :    
                zero.append(zero[i-1] + zero[i-2])
                one.append(one[i-1] + one[i-2])
        print(zero[n], one[n])
    
    fibo(int(input()))
                

