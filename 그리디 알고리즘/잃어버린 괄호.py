inputs = list(input())

for i, v in enumerate(inputs) :
    if v == "-" :
        inputs.insert(i + 1, "(")
        for j, u in enumerate(inputs[i + 2:]) :
            if u == "-" :
                inputs.insert(i + 2 + j, ")")
                break
        if ")" not in inputs[i:] :
            inputs.append(")")
        
evals = []
tmp = ""
for i in inputs :
    if i.isdigit() :
        tmp += i 
    else :
        if tmp :
            evals.append(int(tmp))
            tmp = ""
        evals.append(i)
evals.append(tmp)

print(eval("".join(list(map(str, evals)))))

