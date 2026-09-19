#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define GRIDSIZE 1000

typedef struct { int x, y; } tuple;

tuple DIRECTIONS[4] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

typedef struct {
    tuple  *keys;
    char   *used;
    size_t  capacity;
    size_t  size;
} tuple_set;

tuple move(tuple current, tuple beacon){
    return (tuple){(current.x + beacon.x)/2, (current.y + beacon.y)/2};
}
/* ---------- AI-generated set-handling functions  ---------- */
static size_t next_pow2(size_t n){ size_t p=1; while(p<n) p<<=1; return p; }

static uint64_t hash_tuple(tuple t){
    uint64_t h = (uint64_t)(uint32_t)t.x * 0x9E3779B97F4A7C15ULL;
    h ^= (uint64_t)(uint32_t)t.y * 0xC2B2AE3D27D4EB4FULL;
    h ^= h >> 33; h *= 0xFF51AFD7ED558CCDULL; h ^= h >> 33;
    return h;
}

void set_init(tuple_set *s, size_t min_capacity){
    s->capacity = next_pow2(min_capacity < 8 ? 8 : min_capacity);
    s->keys = malloc(s->capacity * sizeof(tuple));
    s->used = calloc(s->capacity, sizeof(char));
    s->size = 0;
}

int set_contains(const tuple_set *s, tuple t){
    size_t mask = s->capacity - 1, idx = hash_tuple(t) & mask;
    while(s->used[idx]){
        if(s->keys[idx].x == t.x && s->keys[idx].y == t.y) return 1;
        idx = (idx + 1) & mask;
    }
    return 0;
}

static void set_grow(tuple_set *s){
    tuple *ok = s->keys; char *ou = s->used; size_t oc = s->capacity;
    s->capacity = oc * 2;
    s->keys = malloc(s->capacity * sizeof(tuple));
    s->used = calloc(s->capacity, sizeof(char));
    s->size = 0;
    size_t mask = s->capacity - 1;
    for(size_t i = 0; i < oc; i++){
        if(!ou[i]) continue;
        tuple t = ok[i]; size_t idx = hash_tuple(t) & mask;
        while(s->used[idx]) idx = (idx + 1) & mask;
        s->used[idx] = 1; s->keys[idx] = t; s->size++;
    }
    free(ok); free(ou);
}

int set_insert(tuple_set *s, tuple t){
    if(s->size * 10 >= s->capacity * 7) set_grow(s);
    size_t mask = s->capacity - 1, idx = hash_tuple(t) & mask;
    while(s->used[idx]){
        if(s->keys[idx].x == t.x && s->keys[idx].y == t.y) return 0;
        idx = (idx + 1) & mask;
    }
    s->used[idx] = 1; s->keys[idx] = t; s->size++;
    return 1;
}
void print_grid(tuple_set *visited){
    for(int i = 0; i < GRIDSIZE; i++){
        for(int j = 0; j < GRIDSIZE; j++){
            tuple current = {i,j};
            if(set_contains(visited, current)){
                printf("X");
            }
            else printf(".");
        }
        printf("\n");
    }
}
/* --------------------------------------------------------------------- */

typedef struct queue{
    tuple *data;
    size_t capacity;
    size_t head;
    size_t tail;
} queue;

queue* queue_init(){
    queue* q = (queue*)malloc(sizeof(queue));
    q->head = 0;
    q->tail = 0;
    q->capacity = 1 << 16;
    q->data = malloc(q->capacity * sizeof(tuple));
    return q;
}
void queue_insert(queue *q, tuple t){
    if(q->tail == q->capacity){
        q->capacity *= 2;
        q->data = realloc(q->data, q->capacity * sizeof(tuple));
    }
    q->data[q->tail] = t;
    q->tail++;
}
int queue_isempty(queue *q){
    if(q->head >= q->tail){
        return 1;
    }
    return 0;
}
tuple queue_get(queue *q){
    tuple item = q->data[q->head];
    q->head++;
    return item;
}

int main(void){
    tuple start = {0,0};
    tuple a = {0,0}, b = {549,24}, c = {303,539};
    tuple beacons[3] = {a,b,c};

    tuple_set visited;
    set_init(&visited, 1 << 16);

    /* growable BFS queue */
    queue *q = queue_init();

    set_insert(&visited, start);
    queue_insert(q, start);
    while(!queue_isempty(q)){
        tuple cur = queue_get(q);
        for(int k = 0; k < 3; k++){
            tuple nxt = move(cur, beacons[k]);
            if(set_insert(&visited, nxt)){
                queue_insert(q, nxt);
            }
        }
    }

    /* frontier = fireflies, same definition as before */
    tuple_set f;
    set_init(&f, 1 << 16);
    for(size_t i = 0; i < visited.capacity; i++){
        if(!visited.used[i]) continue;
        tuple center = visited.keys[i];
        for(int j = 0; j < 4; j++){
            tuple pos = { center.x + DIRECTIONS[j].x, center.y + DIRECTIONS[j].y };
            if(!set_contains(&visited, pos))
                set_insert(&f, pos);
        }
    }

    printf("illuminated: %zu\n", visited.size);
    printf("fireflies:   %zu\n", f.size);
    print_grid(&visited);
    return 0;
}
