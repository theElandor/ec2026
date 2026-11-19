import sys
from collections import defaultdict
VISITED = set()
S = set()
def dfs(G, start):
    if start in VISITED:
        return
    S.add(start)
    VISITED.add(start)
    for need in G[start]:
        dfs(G, need)
filename = sys.argv[1]
G = defaultdict(list)
data = open(filename).read().splitlines()
for line in data:
    target = line.split(":")[0]
    needs = line.split(":")[1].split(",")
    for need in needs:
        G[need].append(target)
print(G)
dfs(G,"NULLv1")
S.remove("NULLv1")
FIRST = S.copy()
S.clear()
VISITED.clear()
dfs(G,"NULLv2")
S.remove("NULLv2")
SECOND = S.copy()
S.clear()
VISITED.clear()
dfs(G,"NULLv3")
S.remove("NULLv3")
THIRD = S.copy()
S.clear()
VISITED.clear()
counter =0
print(FIRST)
print(SECOND)
print(THIRD)
counter = 0
sol = set()
for x in FIRST:
    if x in SECOND or x in THIRD:
        sol.add(x)

for x in SECOND:
    if x in FIRST or x in THIRD:
        sol.add(x)

for x in THIRD:
    if x in FIRST or x in SECOND:
        sol.add(x) 

print(len(sol))