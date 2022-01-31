#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct t4_ign
{
    char title[MAX];
    char platform[MAX];
    int score;
    int release_year;
    struct t4_ign* following;
}*head = NULL, *current, *newcur;

// The CSV parser
int next_field( FILE *f, char *buf, int max ) {
    int i=0, end=0, quoted=0;
    
    for(;;) {
        // fetch the next character from file
        buf[i] = fgetc(f);
        // if we encounter quotes then flip our state and immediately fetch next char
        if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
        // end of field on comma if we're not inside quotes
        if(buf[i]==',' && !quoted) { break; }
        // end record on newline or end of file
        if(feof(f) || buf[i]=='\n') { end=1; break; }
        // truncate fields that would overflow the buffer
        if( i<max-1 ) { ++i; }
    }

    buf[i] = 0; // null terminate the string
    return end; // flag stating whether or not this is end of the line
}

// From assignment 0
void fetch_file (  FILE *csv, struct t4_ign *point) {
    char buf[MAX];
    next_field( csv, point->title, MAX );      // name and type are just strings so read
    next_field( csv, point->platform, MAX );   // those directly into the struct
    next_field( csv, buf, MAX ); // atoi stands for ASCII to Integer
    point->score = atoi(buf);     // It converts strings to numbers
    next_field( csv, buf, MAX ); // It is not a totally safe function to use.
    point->release_year = atoi(buf);
    
}

void insertValue(struct t4_ign** order, struct t4_ign* cur){
    if(*order==NULL || (*order)->score <= cur->score){
        cur->following = *order;
        *order = cur;
    }
    else{
        newcur = *order;
        while(newcur->following!=NULL && newcur->score >= cur->score)
            newcur=newcur->following;
        cur->following=newcur->following;
        newcur->following=cur;
    }
}

void sort(struct t4_ign **head)
{
    struct t4_ign *sort = NULL;
    current = *head;
    while (current != NULL)
    {
        struct t4_ign *p = current->following;
        insertValue(&sort, current);
        current = p;
    }
    *head = sort;
}

void list(FILE *f)
{
    while(!feof(f))
         {
             struct t4_ign *new;
             new=(struct t4_ign *)malloc(sizeof(struct t4_ign));
             fetch_file( f, new );
             new->following=NULL;
             if(head==NULL){
                 head=new;
                 current=new;
             }
             else{
                 current->following=new;
                 current=new;
             }
         }
}

void printList(struct t4_ign *p )
{
    for (int i=0; i<10;i++)
    {
        p=p->following;
        printf("\n %s\t\t%s\t\t%d\t\t%d\n",p->title,p->platform,p->score,p->release_year);
    }
}


int main ( int argc, char *argv[] ) {
    FILE *f = fopen(argv[1], "r");
    if(!f) {
        printf("unable to open %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    list(f);
    sort(&head);
    printList(head);
    fclose(f);
    return EXIT_SUCCESS;
}
