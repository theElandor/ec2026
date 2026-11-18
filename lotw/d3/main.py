def convert(iso, val):
    conversion = 0
    for i in range(len(val)):
        current = int(val[i])
        conversion += (current*(int(iso[i%len(iso)]))**i)
    return conversion

def solve(line):
    print(f"checking -> {line}")
    standard = line[0].split("-")[1]
    val = line[1]
    #print(standard,val)
    s = standard[::-1]
    v = val[::-1]
    conversion = convert(s, v)
    print(conversion)
    for value in range(int(val)):
        test = convert(s, str(value)[::-1])
        #print(test)
        if test == conversion:
            return 0
    return conversion


filename = "input.txt"
data = [x.split() for x in open(filename).read().splitlines()]
s = 0
for line in data:
    print("------")
    s += solve(line)
print(s)
