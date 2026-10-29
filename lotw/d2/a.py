import sys
from collections import defaultdict
def solve(x:str):
  checksum = ""
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
  for k in sorted(G, key=lambda k: len(G[k]), reverse=True):
    checksum += str(k)
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
