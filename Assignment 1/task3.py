
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_STRING_SIZE 256
#define ARRAY_SIZE 59

int collisions=0;
int addc = 1;

typedef struct Element{
    int freq;
    char* name;
} Element;

Element* hash_table[ARRAY_SIZE];

int hash_function(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s) % ARRAY_SIZE;
        s++;
        
    }
    return hash;
}

int hash3(char* s){
    int hash = 0;
    while(*s){
        hash = 1+ (hash + *s) % (ARRAY_SIZE-1);
        s++;
    }
    return hash;
}

void init_hash_table(){int i;
    for(i = 0; i < ARRAY_SIZE; i++){
        hash_table[i] = NULL;
        
    }
}

Element* createNewElement(char* name){
    Element* newElement = (Element*) malloc (sizeof(Element));
    newElement->name = (char*) malloc (strlen(name) + 1);
    newElement->freq = *(int*) malloc (sizeof(int));
    strcpy(newElement->name, name);
    newElement->freq = 1;
    return newElement;
    
}

Element* search (char* name){
    int index=hash_function(name);
    int i;
    for(i=0;i<ARRAY_SIZE;i++){
        int s = (index+i)%ARRAY_SIZE;
        if(hash_table[s]!=NULL && strcmp(hash_table[s]->name, name)==0){
            return hash_table[s];
        }
    }
        return NULL;
}
// assuming that no element of key name is in the list (use search first!), add element at the correct place in the list
// NB: it would be more efficient for search to return the index where it should be stored directly, but aiming for simplicity here!
bool insert(Element* p){
    if (p == NULL) {
        return false;
    }
    int index = hash_function(p->name);
    int offset = hash3(p->name);

    if (hash_table[index] != NULL){
        while(hash_table[index]!=NULL){
            index++ ;
            index = (index+offset) % ARRAY_SIZE;
            collisions++;
        }
    }
    hash_table[index] = p;
    return true;
}
//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(char* name){
    Element* temp = search(name);
    Element *b=createNewElement(name);
    //int addc = 0;
    if(temp == NULL){
        addc++;
      //  printf("load in null\n");
        insert(b);
    }
    else{
        temp->freq++;
    }
}

void printNumberOfOccurences(char* name){
    int count=0;
    Element *b=search(name);
    if(b==NULL){
        count=0;
        printf("%s not in table\n", name);
    }
    else{
        count=b->freq;
        printf("%s  %d \n", name, count);
    }
}
//
// function from the assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token ( char *buf, FILE *f, int string_max ) {
    // start by skipping any characters we're not interested in
    buf[0] = fgetc(f);
    while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
    // read string of alphanumeric characters
    int i=1;
    for (;;) {
        buf[i] = fgetc(f);                // get next character from file
        if( !isalnum(buf[i]) ) { break; } // only load letters and numbers
        if( feof(f) ) { break; }          // file ended?
        if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
    }
    buf[i] = '\0'; // NULL terminate the string
}


//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file (char *fname )
{
    FILE *f;
    char buf[MAX_STRING_SIZE];

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f)
    {
        printf("Unable to open %s\n", fname);
        return 0;
    }
    // read until the end of the file
    while ( !feof(f) ) {
        next_token(buf, f, MAX_STRING_SIZE);
        addOrIncrement(buf);                           //here you call your function from above!
    }

    fclose(f);
    return 1;
}


int main()
{
    init_hash_table();
    load_file("file name");
    

    printf("Capacity: %d\n",ARRAY_SIZE);
    printf("Num Terms: %d\n",addc);
    printf("Collisions: %d\n", collisions);
    printf("Load: %0.2f\n",(float)addc/ARRAY_SIZE);
    printf("Enter term to get frequency or type \"quit\" to escape\n");
    
    char scan;
    bool flag=false;
    while(flag!=true){
        scanf("%s",&scan);
        if(!strcmp(&scan,"quit")){
            break;
            }
        printNumberOfOccurences(&scan);
    }
}
