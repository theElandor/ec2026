import sys
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

grid = expand_land(grid)
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
print(counter)
print_grid(grid)