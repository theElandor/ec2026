#ifndef SET_H
#define SET_H
#define SET_LIMIT_SIZE 1000

typedef struct SetNode {
  struct SetNode* next;
  int value;
} SetNode;

typedef struct Set {
  SetNode** nodes;
  int currLength;
} Set;


unsigned int fnv1a_int(int value);
int itemIndex(int value, int arrLimit);
Set* initializeSet();
SetNode* createNode(int value);
void insert(Set* set, int value);
int isEmpty(Set* set);
SetNode* find(Set* set, int value);
int removeItem(Set* set, int value);

#endif
