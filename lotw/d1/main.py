import sys
import math
filename = sys.argv[1]
vals = [int(x) for x in open(filename).read().strip().split(",")]
s = []
for x in vals:
    outside = max(3,math.ceil(math.sqrt(x)))
    inside = outside-2
    needed = (outside**2) - (inside**2) - x
    while needed < 0:
        outside+=1
        inside +=1
        needed = (outside **2) - (inside **2) - x
    s.append(needed)
print(sum(s))

