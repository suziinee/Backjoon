from collections import deque
string = list(input())

def confirm(string) :
    s = deque(string)
    stack = []
    while s :
        x = s.popleft()
        if x in ["[", "("] :
            stack.append(x)
        else :
            if stack :
                if stack[-1] == "(" and x == ")" :
                    stack.pop()
                    continue
                if stack[-1] == "[" and x == "]" :
                    stack.pop()
            else :
                stack.append(x)
    if stack :
        return False
    else :
        return True


def func(string) :

    score = {"(" : 2, "[" : 3}
    pair = {"(" : ")", "[" : "]"}
    string = deque(string)

    stack = []
    res = 0
    flag = 0

    while string :
        x = string.popleft()
        # (, [ 의 경우
        if x in score :
            flag = 0
            stack.append(x)
            continue

        # ), ] 의 경우
        if pair[stack[-1]] == x :
            # stack에 쌓인 애들 곱해서 계산
            if flag == 0 :
                ans = 1
                for s in stack :
                    ans *= score[s]
                res += ans
                flag = 1

            # 짝 발견할 때까지 pop
            if flag == 1 :
                stack.pop()

    return res


if confirm(string) :
    print(func(string))
else :
    print(0)