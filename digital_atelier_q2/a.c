#include "stdio.h"
#include "set.h"
#include "string.h"
#include "stdint.h"
char *MOVES = {"CABBCABCCCBBBBAABABACCBAAAACAABCABACBAABCCBCBABCBBACCCCCAAAABCBBCBCBACAABBCCBACBBAAACBBACBCABBABBACB\0"};
typedef struct tuple{
    int x;
    int y;
} tuple;
tuple move(tuple current, tuple beacon){
    return (tuple){(current.x + beacon.x)/2, (current.y + beacon.y)/2};
}
void tuple_printTuple(tuple a){
    printf("(%d, %d)\n", a.x, a.y);
}
int linear_find(tuple *arr, int len, tuple t){
    for(int i = 0; i < len; i++){
        if(t.x == arr[i].x && t.y == arr[i].y)
            return 1;
    }
    return 0;
}
int main(int argc, char **argv){
    tuple a = {0,0};
    tuple b = {20,0};
    tuple c = {10, 20};
    tuple current = {10,0};
    tuple visited[1000];
    int visited_len = 0;
    visited[visited_len++] = current;
    int nx, ny;
    for(int i = 0; i<strlen(MOVES); i++){
        char dir = MOVES[i];
        if(dir== 'A') current = move(current, a);
        else if (dir == 'B')current = move(current, b);
        else current = move(current, c);
        tuple_printTuple(current);
        if(!linear_find(visited, visited_len, current)){
            visited[visited_len++] = current;
        }
    }
    printf("%d\n", visited_len);
    return 0;
}
