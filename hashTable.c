#include "hashTable.h"

//String hashing from K&R's "The C Programming Language"
unsigned Hash(char *key) {
    unsigned hash;

    for(hash=0; *key != '\0'; key++){
        hash = *key + 31 * hash;
    }

    return hash % MAX_BUCKETS;
};

//creating hashtable
HashTable* CreateHashTable() { 
    HashTable *h = (HashTable*) malloc(sizeof(HashTable)); //allocating hashtable in the memory

    for(int i=0; i < MAX_BUCKETS; i++){
        h->buckets[i] = NULL;  //seting every bucket for null
        h->numElements[i] = 0;
    }

    return h;
};

//Using chaining probing to handle collisions.
void Insert(HashTable *h, char *key) { //Using chaining probing to handle collisions.
    if (!h)
        h = CreateHashTable(); 
    
    unsigned hashNumber = Hash(key);                                  //aplying the hash function to the word received
    
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node)); //allocating node in the memory
    newNode->key = (char*) malloc(MAX_STRING * sizeof(char));         //allocating string in the memory

    strcpy(newNode->key, key);                                         //copying the word received to the node key
    newNode->next=NULL;


    if(!h->buckets[hashNumber]){                   //if the bucket related to the hash number is empty
        h->buckets[hashNumber] = newNode;          //seting this bucket to the node previously created
        h->numElements[hashNumber]++;              //increasing the number of elements in the hashtable
    }
    else{    // if the bucket is already filled
        struct Node* aux = h->buckets[hashNumber]; //creating an auxiliar node

        while(aux->next != NULL){                          //while the node is not the last one, move foward
            aux = aux->next;

        }
        aux->next = newNode;                               //seting the last node to the node previously created
        h->numElements[hashNumber]++;              //increasing the number of elements in the hashtable
        numColisoes++;                                     //increasing the number of colisions for testing purposes
    }
}

bool Search(HashTable *h, char *key) {
    struct Node *aux;

    unsigned hashValue = Hash(key); 
    
    if (!h) {
        printf("Hash Table is empty.\n");
        return false;
    }
    aux = h->buckets[hashValue];

    while(aux){
        if (strcmp(aux->key, key) == 0)
            return true;

        aux = aux->next;
    }
    //printf("%s [%d]\n", key, hashValue = Hash(key)); //Uncomment if you want to print not found words.
    return false;
}

void RemovePunctAndMakeLowerCase(char *key) {
    char *src = key, *dst = key;

    while (*src) {
       if (ispunct((unsigned char)*src)) {
          // Skip this character
          src++;
       }
       else if (isupper((unsigned char)*src)) {
          // Make it lowercase
          *dst++ = tolower((unsigned char)*src);
          src++;
       }
       else if (src == dst) {
          // Increment both pointers without copying 
          src++;
          dst++;
       }
       else {
          // Copy character 
          *dst++ = *src++;
       }
    }

    *dst = 0;
}

/*
void printAll(HashTable *hashtable){                  //an experimental function to see how many elements are in each bucket
    int empty=0,full=0,bucket1=0,bucket2=0,bucket3=0,bucket4=0,bucket5=0,bucket6=0,bucketmaior=0;
    for (int i = 0; i<MAX_BUCKETS;i++){
        if(hashtable->numElements[i]==1){
            bucket1++;
        }else if (hashtable->numElements[i]==2){
            bucket2++;
        }else if(hashtable->numElements[i]==3){
            bucket3++;
        }else if (hashtable->numElements[i]==4){
            bucket4++;
        }else if(hashtable->numElements[i]==5){
            bucket5++;
        }else if (hashtable->numElements[i]==6){
            bucket6++;
        }else if(hashtable->numElements[i]>6){
            bucketmaior++;
        }
        
        //printf("Bucket: [%d], Numero de elementos: %d\n",i,hashtable->numElements[i]);
    }
    printf("Buckets com 1: %d\nBuckets com 2: %d\nBuckets com 3: %d\nBuckets com 4:%d\nBuckets com 5 :%d\nBuckets com 6:%d\nBuckets com mais de 6:%d\n",bucket1,bucket2,bucket3,bucket4,bucket5,bucket6,bucketmaior);
    //printf("Buckets vazios:%d Buckets preenchidos:%d\n", empty,full);
}
*/