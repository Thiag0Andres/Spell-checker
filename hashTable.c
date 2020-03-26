#include "hashTable.h"

HashTable* createHashTable() {
    HashTable *h = (HashTable*) malloc (sizeof(HashTable));

    for(int i=0; i < MAX_BUCKETS; i++){
        h->buckets[i] = NULL;
        h->numElements[i] = 0;
    }

    return h;
};

unsigned Hash(char *key) {
    unsigned hash;

    for(hash=0; *key != '\0'; key++){
        hash = *key + 31 * hash;
    }

    return hash % MAX_BUCKETS;
};

void Insert(HashTable *h, char *key) {
    
};

bool Search(HashTable *h, char *key) {
    
};

void RemovePunctAndMakeLowerCase(char *key) {

};