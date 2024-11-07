#ifndef C_LIST_H
#define C_LIST_H

typedef enum {
    int_type,  
    float_type, 
    string_type
} list_data_type;


void** create();
void** append(void** ptr, int* size, void* item, list_data_type type);
void** pop(void** ptr, int* size);
void print(const void** ptr, int size);
void destroy(void** ptr);

#endif
