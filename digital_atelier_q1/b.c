#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "set.h"

void print_arr(int *arr, size_t len){
    for(int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
// actual function that solves the problem.
int solve(int *jumps, size_t len){
    Set* set = initializeSet();
    insert(set,0);
    int position = 0;
    int newpos;
    for(size_t i = 0; i < len; i++){
        newpos = position - jumps[i];
        if(find(set, newpos) || newpos < 0){
            newpos = position + jumps[i];
            while (find(set, newpos)){
                newpos++;
            }
        }
        if(!find(set,newpos)) insert(set, newpos);
        position = newpos;
        //printf("%d ",position);
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
                total += partial;
                len = 0;
            }
        }
    } 
    printf("%d\n", total);
    return 0;
}
