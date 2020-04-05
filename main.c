#include <time.h>
#include "hashTable.h"

int main() {
    //opening the input, output and the dictionary text files
    FILE *input = fopen("Texto bases/Harry_Potter_and_the_Order_of_Phoenix.txt", "r");
    FILE *output = fopen("relatorio.txt", "w");
    FILE *dictionary = fopen("ascii_noaccent_noduplicates_FIXED_v2.txt","r");
    
    char dictionaryStr[MAX_STRING], inputStr[MAX_STRING];
    char space[] = " ";
    char *token = NULL;
    clock_t time[2] = {0,0};
    int wordNotFound = 0;
    int numWords = 0;

    HashTable *hashTable = CreateHashTable(hashTable);          //creating hashtable

    while (fgets(dictionaryStr, MAX_STRING, dictionary)){       //Insert dictionary in HashTable
        if(dictionaryStr[strlen(dictionaryStr) - 1] == '\n')    //if the last char in the string is a \n change to a \0
            dictionaryStr[strlen(dictionaryStr) - 1] = '\0';
        Insert(hashTable, dictionaryStr);
    }
    
    while (fgets(inputStr, MAX_STRING, input)){                 //Search words from input text
        RemovePunctAndMakeLowerCase(inputStr);

        if(inputStr[strlen(inputStr) - 1] == '\n')
            inputStr[strlen(inputStr) - 1] = '\0';

        time[0] += clock();                                     //seting the initial time of execution        
        token = strtok(inputStr, space);
        
        while( token != NULL ) {
            numWords++;
            
            if(!Search(hashTable, token))                       //if the word is not found in the dictionary
                wordNotFound++;
    
            token = strtok(NULL, space);
        }
        time[1] += clock();
    }

    //print the execution report 
    fprintf(output, "Numero total de palavras do texto: %d.\n", numWords);
    fprintf(output, "Numero total de palavras que falharam no spell check: %d.\n", wordNotFound);
    fprintf(output, "Tempo total da verificacao: %.2lf ms.\n", (double) (time[1] - time[0]) * 1000.0 / CLOCKS_PER_SEC);
    
     //closing the archives
    fclose(input);
    fclose(output);
    fclose(dictionary);
    return 0;
}