long FileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    long Size = ftell(file);
    rewind(file);
    return Size;
}

unsigned char * File_To_Buf(FILE * file){
    long Size = FileSize(file);
    unsigned char *buf = (unsigned char *) calloc(Size, 1);
    size_t New_Size = fread(buf, 1, Size, file);
    unsigned char * new_buf = (unsigned char *)calloc(New_Size + 1, sizeof(unsigned char));
    for (int i = 0; i < New_Size; i++){
        new_buf[i] = buf[i];
    }
    new_buf[New_Size] = '\0';
    free(buf);
    fclose(file);
    return new_buf;
}

unsigned Number_Of_Lines(const char * buf){
    unsigned i = 0;
    char * a = (char *) buf;
    while (1){
        a = strchr(a, '\n');
        if (!a) break;
        a++;
        i++;
    }
    return i;
}

unsigned char * The_End_Of_The_Word(const unsigned char * source){
    unsigned char * ptr = (unsigned char *) source;
    while (1){
        if (!isalpha(*ptr)) break;
        if (*ptr == '\n') break;
        if (*ptr == '\r') break;
        if (*ptr == '\0') break;
        ptr++;
    }
    return ptr;
}

unsigned char * Skip_Different_Shit(const unsigned char * source){
    unsigned char * ptr = (unsigned char * )source;
    while (1){
        if (isalpha(*ptr)) break;
        ptr++;
    }
    return ptr;
}

char * New_String_Lessmem(char * new_person){
    char * end = strchr(new_person, '\0');
    char * new_person_lessmem = (char *) calloc(end - new_person + 1, sizeof(char));
    sscanf(new_person,"%s", new_person_lessmem);
    free(new_person);
    return new_person_lessmem;
}