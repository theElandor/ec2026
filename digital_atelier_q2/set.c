#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"




// 32-bit FNV-1a
unsigned int fnv1a_int(int value) {
  unsigned int hash = 2166136261u;
  unsigned char* p = (unsigned char*)&value;

  for(int i = 0; i < (int)sizeof(int); i++) {
    hash ^= (unsigned int)p[i];
    hash *= 16777619u;
  }

  return hash;
}

int itemIndex(int value, int arrLimit) {
  unsigned int hash = fnv1a_int(value);
  return hash % arrLimit;
}

Set* initializeSet() {
  Set* set = malloc(sizeof(Set));
  set->currLength = 0;
  set->nodes = malloc(sizeof(SetNode*) * SET_LIMIT_SIZE);

  for(int i = 0; i < SET_LIMIT_SIZE; i++) {
    set->nodes[i] = NULL;
  }

  return set;
}

SetNode* createNode(int value) {
  SetNode* newNode = malloc(sizeof(SetNode));
  newNode->next = NULL;
  newNode->value = value;
  return newNode;
}

void insert(Set* set, int value) {
  int index = itemIndex(value, SET_LIMIT_SIZE);
  SetNode* currentNode = set->nodes[index];

  SetNode* prevNode = NULL;
  while(currentNode != NULL) {
    if(currentNode->value == value) {
      printf("set do not allow repeated values: %d\n", value);
      return;
    }
    prevNode = currentNode;
    currentNode = currentNode->next;
  }

  SetNode* newNode = createNode(value);
  set->currLength += 1;

  if(prevNode == NULL) {
    set->nodes[index] = newNode;
  } else {
    prevNode->next = newNode;
  }
}

int isEmpty(Set* set) {
  return set->currLength == 0;
}

SetNode* find(Set* set, int value) {
  if(isEmpty(set))
    return NULL;

  int index = itemIndex(value, SET_LIMIT_SIZE);
  SetNode* currNode = set->nodes[index];

  while(currNode != NULL && currNode->value != value) {
    currNode = currNode->next;
  }

  return currNode;
}

int removeItem(Set* set, int value) {
  if(isEmpty(set))
    return -1;

  int index = itemIndex(value, SET_LIMIT_SIZE);
  SetNode* currentNodeToDelete = set->nodes[index];

  SetNode* prevNode = NULL;
  while(currentNodeToDelete != NULL && currentNodeToDelete->value != value) {
    prevNode = currentNodeToDelete;
    currentNodeToDelete = currentNodeToDelete->next;
  }

  if(currentNodeToDelete == NULL)
    return -1;

  if(prevNode != NULL) {
    prevNode->next = currentNodeToDelete->next;
  } else {
    set->nodes[index] = currentNodeToDelete->next;
  }

  free(currentNodeToDelete);
  set->currLength -= 1;

  return 1;
}
