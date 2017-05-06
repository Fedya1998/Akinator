#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <cstring>
#include <errno.h>
#include <ctype.h>
#include <malloc.h>
#include <clocale>
#include <new>


#define DEBUG 10

#ifdef DEBUG
#define Gde printf("Line %d, Function %s\n", __LINE__, __PRETTY_FUNCTION__)
#define Err;\
printf("Error %x\n", errno);\
Gde;
#define SUPER_NOT_OK_DUMP(wat);\
{\
    if (!wat##_OK(This)){\
        wat##_Dump(This);\
        assert(!"Ok_failed");\
    };\
}
#define p(n, code) if (DEBUG >= n) {printf code;}
#define d(n, code) if (DEBUG >= n) {code;}
#else
#define SUPER_NOT_OK_DUMP(wat)
#define assert(x)
#define DEBUG 0
#define d(arg, code)
#define p(arg, code)
#define Gde
#define Err
#endif


const int MAX_LINES = 10;
FILE * super_tree_dump = fopen("dump.gv", "w");

typedef struct elem{
    char * value = NULL;
    struct elem * right = NULL;
    struct elem * left = NULL;
    struct elem * previous = NULL;
    struct tree_header * header = NULL;
};


typedef struct tree_header{
    elem * first = NULL;
    int count = 0;
};

tree_header * Tree_Ctor(void);
int Tree_Dtor(tree_header * header1);
void Delete_Element(elem * element);
bool Elem_And_Next_OK(const elem *element);
bool Tree_OK(const tree_header *header);
bool Elem_OK(const elem * element);
void Elem_Dump(const elem *element);
void Mini_File_Dump(const elem * element);
void Elem_And_Next_Dump(const elem * elm);
void Tree_Dump(const tree_header *header);
elem * Add_First(tree_header * header);
elem * Add_Left(elem * element);
elem * Add_Right(elem * element);

void Tree_To_File(const tree_header * header);
void Tree_To_File_Mini(const elem * element, FILE * akin);
tree_header* File_To_Tree(const FILE * source);
elem * File_To_Tree_Mini(char ** buf, tree_header * header);
elem * Define_Me(const tree_header * header);
elem * Mini_Define(elem * element);
elem * Add_Person(elem * element);






unsigned char * File_To_Buf(FILE * file);
long FileSize(FILE *file);
unsigned char * The_End_Of_The_Word(unsigned char * source);
char * New_String_Lessmem(char * new_person);





int main() {
    FILE * akin = fopen("akinator.txt", "r");
    tree_header * header = File_To_Tree(akin);

    printf("\nTree construct process have just finished successfully\n\n");
    Tree_Dump(header);



    Define_Me(header);

    Tree_To_File(header);



    Tree_Dtor(header);



    return 0;
}


#include "Tree_Functions.h"
#include "Akinator_Functions.h"
#include "my_functions.h"