#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "set.h"
#define MAXLEN 100000
#define MAXUNTANGLE 10000
// error: to check crossing we must check if we go before the start of another jump
// or after the end!

// first backwards, if dest is positive and alredy visited, move forwad
// if a forward lands on a visited, then increase by 1 untill you find an unvisited
// if a backwards crosses, try forward
// if a forward crosses, then increase by 1 untill untill no crossing
// if no valid forward exists, then skip and go to next jump
typedef struct tuple{
    int start;
    int end;
} tuple;
typedef struct rangearr{
    tuple ranges[MAXLEN];
    int len;
}rangearr;
void rangearr_init(rangearr *v){v->len=0;}
void rangearr_push(rangearr *v, tuple t){
    v->ranges[v->len] = t;
    v->len++;
}
void print_arr(int *arr, size_t len){
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int crosses(int oldpos, int newpos, int side, rangearr *ranges_up, rangearr *ranges_down){
    rangearr *refrange = (side == 1) ? ranges_up : ranges_down;
    int left, right;
    if(oldpos > newpos){left = newpos; right = oldpos;}
    else{left = oldpos; right = newpos;}
    for(int i = 0; i < refrange->len; i++){
        tuple range = refrange->ranges[i];
        if(left > range.start && left < range.end && right > range.end){return 1;}
        if(right > range.start && left < range.start && right < range.end){return 1;}
    }
    return 0;
}
void update_crossed(int position, int newpos, int side, rangearr *ranges_up, rangearr *ranges_down){
    rangearr *refrange = (side == 1) ? ranges_up : ranges_down;
    tuple range;
    // backward
    if (position > newpos){ range.start = newpos; range.end = position;}
    else{range.start = position;range.end = newpos;}
    rangearr_push(refrange, range);
}

int forward(int position, int jump, Set *visited){
    // guarantees to land on a unvisited point
    int newpos = position + jump; // forward
    while (find(visited, newpos)){
        newpos++;
    }
    return newpos;
}
int untangle(int position, int newpos, int side, rangearr *ranges_up, rangearr *ranges_down, Set *visited){
    int loops = 0;
    while (crosses(position, newpos, side, ranges_up, ranges_down) || find(visited, newpos)){
        newpos++;
        loops++;
        if (loops > MAXUNTANGLE){return -1;}
    }
    return newpos;
}
int solve(int *jumps, size_t len){
    Set* visited = initializeSet();
    rangearr ranges_up;
    rangearr ranges_down;
    rangearr_init(&ranges_up);
    rangearr_init(&ranges_down);
    insert(visited,0);
    int position = 0;
    int newpos;
    int side = 0; // 0 -> down 1 -> up
    int possible;
    for(size_t i = 0; i < len; i++){
        possible = 1;
        newpos = position - jumps[i]; // backward
        if(find(visited, newpos) || newpos < 0){ // if alredy visited or negative
            newpos = forward(position, jumps[i], visited);
            newpos = untangle(position, newpos, side, &ranges_up, &ranges_down, visited);
        }
        // if backward jump crosses
        if (crosses(position, newpos, side, &ranges_up, &ranges_down)){
            // try forward
            newpos = forward(position, jumps[i], visited);
            newpos = untangle(position, newpos, side, &ranges_up, &ranges_down, visited);
        }
        if (newpos == -1) continue; // go to next jump, don't update anything
        if(!find(visited,newpos)) insert(visited, newpos);
        update_crossed(position, newpos, side, &ranges_up, &ranges_down);
        side = (side+1)%2;
        position = newpos;
    }
    return position;
}
// some code to read comma separated unsinged integers
// that can be reused
int main(int argc, char **argv){
    FILE *file;
    file = fopen(argv[1], "r");
    if(!file){
        perror("opening file\n");
        return 1;
    }
    int total = 0;
    int jumps[2000];
    int partial;
    size_t len = 0;
    char line[10000];
    int c;
    unsigned value = 0;
    int reading_number = 0;
    while ((c = fgetc(file)) != EOF) {
        if (isdigit(c)) {
            value = value * 10 + (c - '0');
            reading_number = 1;
        }
        else if (c == ',' || c == '\n') {
            if (reading_number) {
                jumps[len++] = value;
                value = 0;
                reading_number = 0;
            }
            if (c == '\n') {
                int partial = solve(jumps, len);
                printf("%d ", partial);
                total += partial;
                len = 0;
            }
        }
    } 
    printf("\n%d\n", total);
    return 0;
}
