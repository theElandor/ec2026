from collections import defaultdict

def assign_points(times):
    # times -> {1:[2,4,6], 2:[10, 15]}
    points = defaultdict(int)
    #print(times)
    for part in range(3):
        X = []
        for ide,T in times.items():
            if len(T) <= part: X.append((ide,0))
            else: X.append((ide, T[part]))
        X = sorted(X, key=lambda x:x[1])
        print(X)
        # we have the sorting, we assign the points for the part
        current_score = 50*(part+1)
        dups = 0
        for i in range(len(X)):
            player, time = X[i]
            if time == 0: continue
            print(f"player {player} gets {current_score}")
            points[player] +=  current_score
            if i != len(X)-1:
                if time != X[i+1][1]:
                    current_score = max(current_score-1-dups, 0)
                    dups = 0
                else:
                    dups += 1
    print(points)
    return points

filename = "input"
data = open(filename).read().splitlines()
TOTAL = defaultdict(int)
tuples = []
times = defaultdict(int)
parts = defaultdict(list)
for line in data:
    ID, quest, part, time = line.split()
    tuples.append((int(ID[3:]), int(quest[6:]), int(part[5:]), int(time[5:])))
all_quests = set([quest for ide, quest, part, time in tuples])
for Q in sorted(all_quests):
    print(f"QUEST {Q}")
    times = defaultdict(list)
    for P in range(1,4):
        for ide, quest, part, time in tuples:
            if Q != quest or part != P: continue
            times[ide].append(time + (times[ide][-1] if times[ide] else 0))
    points = assign_points(times) 
    for k,v in points.items():
        TOTAL[k] +=v
    print("------------")
    print(TOTAL)
CHECK = 0
scores = sorted(TOTAL.values(), reverse=True)
current_index = 1
dups = 0
for i, current_score in enumerate(scores):
    CHECK += current_score*current_index
    if i != len(scores)-1:
        if scores[i+1] != current_score:
            current_index = current_index +1+dups
            dups = 0
        else:
            dups += 1
print(CHECK)


##T = sorted([(len(parts[ide]), -times[ide]) for ide in list(times.keys())], reverse=True)
##print(T)
##print(sum([(i+1)*x[1] for i,x in enumerate(T)]))
