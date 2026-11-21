# CONVOLUTIONS! :)

import sys
KERNEL = '''
.+++.
+++++
++X++
+++++
.+++.
'''
KERNEL = KERNEL.splitlines()[1:]
print(KERNEL)
DIRECTIONS = [(1,0), (0,1), (1,1), (-1,0), (-1,-1), (-1,1), (0,-1), (1,-1)]
filename = sys.argv[1]
grid = [list(x) for x in open(filename).read().splitlines()]
M = len(grid)
N = len(grid[0])

def print_grid(grid):
    for i in range(M):
        for j in range(N):
            print(grid[i][j], end="")
        print("")

def expand_land(grid):   
    start = (int(M/2), int(N/2))
    grid[start[0]][start[1]] = "#"
    while True:
        new_lands = []
        for r in range(M):
            for c in range(N):
                current = grid[r][c]
                if current == "#": continue
                ones, lands = 0, 0
                for dr, dc in DIRECTIONS:
                    # iterate on neighbors
                    if r + dr not in range(M) or c + dc not in range(N): continue
                    neig = grid[r+dr][c+dc]
                    if neig == "#": lands += 1
                    elif neig == "1": ones += 1
                if (lands + ones) >= 5 and lands >= 1:
                    new_lands.append((r,c))
        if not new_lands: break
        for r,c in new_lands: grid[r][c] = "#" 
        new_lands.clear()
    counter = 0
    for i in range(M):
        for j in range(N):
            if grid[i][j] == "#": counter += 1
    return grid

def sand(grid):
    while True:
        new_sands = []
        for r in range(M):
            for c in range(N):
                current = grid[r][c]
                if current != "#": continue
                sands = 0 
                waters = 0
                for dr, dc in DIRECTIONS:
                    # iterate on neighbors
                    if r + dr not in range(M) or c + dc not in range(N): 
                        new_sands.append((r,c))
                        continue
                    neig = grid[r+dr][c+dc]
                    if neig == "=": sands += 1
                    if neig == "0" or neig == "1": waters += 1
                if waters or sands >= 5: new_sands.append((r,c))
        if not new_sands: break
        for r,c in new_sands: grid[r][c] = "=" 
        new_sands.clear()
    counter = 0
    for i in range(M):
        for j in range(N):
            if grid[i][j] == "=": counter += 1
    return grid

def trees(grid):
    # first step: plant trees
    for r in range(M):
        for c in range(N):
            if grid[r][c] != "#": continue
            cand = True
            for dr in range(-2, 3):
                for dc in range(-2,3):
                    if r+dr not in range(M):
                        cand = False
                        continue
                    if c + dc not in range(N):
                        cand = False
                        continue
                    kernel_value = KERNEL[dr+2][dc+2]
                    grid_value = grid[r+dr][c+dc]
                    if kernel_value == "+":
                        if grid_value not in ["@", "#"]:
                            cand = False
                            continue
            if cand:
                grid[r][c] = "@"
    for step in range(2):
        next_trees = []
        for r in range(M):
            for c in range(N):
                ntrees = 0
                sandneig = False
                if grid[r][c] != "#": continue
                for dr, dc in DIRECTIONS:
                    if r+dr not in range(M) or c+dc not in range(N):
                        continue
                    neig = grid[r+dr][c+dc]
                    if neig == "=":
                        sandneig = True
                    elif neig == "@":
                        ntrees += 1
                if not sandneig and ntrees >= 4:
                    next_trees.append((r,c))
        for r,c in next_trees:
            grid[r][c] = "@"
    return grid

grid = expand_land(grid)
beach = sand(grid)
trees(grid)
print_grid(grid)
counter = 0
for r in range(M):
    for c in range(N):
        if grid[r][c] == "@":
            counter += 1
print(counter)