import sys
import math
filename = sys.argv[1]
vals = [int(x) for x in open(filename).read().strip().split(",")]
# parts 1 and 2
#for x in vals:
#    outside = max(3,math.ceil(math.sqrt(x)))
#    inside = outside-2
#    needed = (outside**2) - (inside**2) - x
#    while needed < 0:
#        outside+=1
#        inside +=1
#        needed = (outside **2) - (inside **2) - x
#    s.append(needed)
#print(sum(s))
# part 3
s =0
for x in vals:
  upper = max(3,math.ceil(math.sqrt(x)))
  if upper % 2 == 0:
    upper+=1
  necess = (upper**2)-1
  if necess < x:
    necess = ((upper+2)**2)-1
  s += (necess-x)
  print(f"{x} -> {necess-x}")
print(s)

