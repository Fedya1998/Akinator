#include <stdlib.h>

tree_header * Tree_Ctor(void) {
    tree_header *header1 = new tree_header();
    header1->count = 0;
    header1->first = NULL;
    return header1;
}

elem * Add_First(tree_header * header){
    assert(header);
    header->first = new elem();
    header->first->header = header;
    header->count++;
    header->first->left = NULL;
    header->first->right = NULL;
    header->first->value = NULL;
    return header->first;
}

int Tree_Dtor(tree_header *header1) {
    elem *element = header1->first;
    Delete_Element(element);
    delete header1;
    return errno;
}

void Delete_Element(elem *element) {
    if (!element) return;
    if (element->right) Delete_Element(element->right);
    if (element->left) Delete_Element(element->left);
    if (element->value) free(element->value);
    printf("Deleting elem\n");
    delete element;
}

bool Elem_OK(const elem * element){
    return element && element->value && element->header;
}

bool Elem_And_Next_OK(const elem *element) {
    bool OK = element && element->header;
    if (element->right) OK = OK && Elem_And_Next_OK(element->right);
    if (element->left) OK = OK && Elem_And_Next_OK(element->left);
    return OK;
}

bool Tree_OK(const tree_header *header) {
    if (!header)
        return 1;
    if (header->count < 0) {
        p(9, ("Bad count"));
        return false;
    }//Bad count
    elem *element = header->first;
    if (element == NULL && header->count == 0) {
        p(9, ("Empty list\n"));
        return true;
    }//If our list is empty
    return Elem_And_Next_OK(element);
}



void Elem_Dump(const elem *element) {
    printf("value %s\n", element->value);
    if (DEBUG) {
        printf("pointer %p\n", element);
        printf("header %p\n", element->header);
        printf("right %p\n", element->right);
        printf("left %p\n", element->left);
    }
}


void Mini_File_Dump(const elem * element){
    fprintf(super_tree_dump, "%celement %p\nprevious %p\nvalue %s\nheader %p\nleft %p\nright %p%c", 34,
            element, element->previous, element->value, element->header, element->left, element->right, 34);
}

void Elem_And_Next_Dump(const elem * elm){
    const elem * element = elm;
    if (!elm) return;

    if (element->left) {

        Mini_File_Dump(element);

        fprintf(super_tree_dump, "->");

        Mini_File_Dump(element->left);
    }

    if (element->left) Elem_And_Next_Dump(element->left);

    if(element->right) {

        Mini_File_Dump(element);
        fprintf(super_tree_dump, "->");
        Mini_File_Dump(element->right);

    }
    if (element->right) Elem_And_Next_Dump(element->right);
}

void Tree_Dump(const tree_header *header) {
    fprintf(super_tree_dump, "digraph G{\n");
    if (!header) return;
    if (!header->first) return;
    Elem_And_Next_Dump(header->first);
    fprintf(super_tree_dump, "}");
    fclose(super_tree_dump);
    system("dot -Tpng dump.gv -o dump.png");
}



elem * Add_Left(elem * element) {
    if (!Elem_OK(element)){
        p(10, ("Not ok in add left elem\n"));
        Elem_Dump(element);
        return NULL;
    }
    tree_header * This = element->header;
    SUPER_NOT_OK_DUMP(Tree);

    element->left = new elem;
    element->left->header = This;
    element->left->previous = element;
    This->count++;
    SUPER_NOT_OK_DUMP(Tree);
    return element->left;
}

elem * Add_Right(elem * element) {
    if (!Elem_OK(element)){
        p(10, ("Not ok in add right elem\n"));
        Elem_Dump(element);
        return NULL;
    }
    tree_header * This = element->header;
    SUPER_NOT_OK_DUMP(Tree);
    element->right = new elem;
    element->right->header = This;
    element->right->previous = element;
    This->count++;
    SUPER_NOT_OK_DUMP(Tree);
    return element->right;
}

