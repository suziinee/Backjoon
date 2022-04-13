cro = ['c=', 'c-', 'dz=', 'd-', 'lj', 'nj', 's=', 'z=']

string = input()

for c in cro :
    string.replace(c, "1")

print(string.count("1"))