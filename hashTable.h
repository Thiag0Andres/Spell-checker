#ifndef HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUCKETS 
#define MAX_STRING

struct node{
    struct Node* next;
    char *key;
};


typedef struct HashTable{
    struct Node* buckets[MAX_BUCKETS];
    int numElements[MAX_BUCKETS];
}HashTable;

extern 


#endif // !HASHTABLE_H