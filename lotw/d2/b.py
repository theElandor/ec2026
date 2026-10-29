import sys
from collections import defaultdict
from collections import deque
def topo_sort(G):
  result = ""
  indegs = {x:0 for x in G.keys()}
  for source, dests in G.items():
    for d in dests: indegs[d]+=1
  Q = deque() 
  for k,v in indegs.items():
    if v == 0:
      Q.append(k)
  while Q:
    node = Q.popleft()
    result += str(node)
    for dest in G[node]:
      indegs[dest]-=1
      if indegs[dest] == 0:
        Q.append(dest)
  return result
def solve(x:str):
  rules = x.split()
  G = {}
  for rule in rules:
    first, second = rule[0], rule[2]
    symbol = rule[1]
    if symbol == "<":
      source, dest = second, first
    else:
      source, dest = first, second
    if int(source) not in G: G[int(source)] = []
    if int(dest) not in G: G[int(dest)] = []
    G[int(source)].append(int(dest))
  checksum = topo_sort(G) 
  print(checksum)
  for k, v in G.items():
    print(f"{k} -> {v}")
  return int(checksum)

filename = sys.argv[1]
lines = open(filename).read().strip().splitlines()
s = 0 
for x in lines:
  s += solve(x)
print(s)
