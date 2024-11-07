#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c_list.h"

static list_data_type* type_array = NULL;
static int type_array_size = 0;

void** create() {
    void** list = malloc(sizeof(void*));
    if (!list) return NULL;
    
    type_array = malloc(sizeof(list_data_type));
    type_array_size = 1;
    
    return list;
}

void** append(void** ptr, int* size, void* item, list_data_type type) {
    void** new_ptr = realloc(ptr, (*size + 1) * sizeof(void*));
    if (!new_ptr) return ptr;

    if (type == string_type) {
        new_ptr[*size] = malloc(strlen((char*)item) + 1);
        strcpy((char*)new_ptr[*size], (char*)item);
    } else {
        new_ptr[*size] = malloc(sizeof(item));
        memcpy(new_ptr[*size], item, sizeof(item));
    }
    
    type_array = realloc(type_array, (*size + 1) * sizeof(list_data_type));
    type_array[*size] = type;

    *size += 1;
    return new_ptr;
}

void** pop(void** ptr, int* size) {
    if (*size == 0) return ptr;

    if (type_array[*size - 1] == string_type) {
        free(ptr[*size - 1]);
    }
    
    type_array = realloc(type_array, (*size - 1) * sizeof(list_data_type));
    *size -= 1;

    return realloc(ptr, *size * sizeof(void*));
}

void print(const void** ptr, int size) {
    for (int i = 0; i < size; i++) {
        if (type_array[i] == int_type) {
            printf("%d ", *(int*)ptr[i]);
        } else if (type_array[i] == float_type) {
            printf("%f ", *(float*)ptr[i]);
        } else if (type_array[i] == string_type) {
            printf("%s ", (char*)ptr[i]);
        }
    }
    printf("\n");
}

void destroy(void** ptr) {
    for (int i = 0; i < type_array_size; i++) {
        if (type_array[i] == string_type) {
            free(ptr[i]);
        }
    }
    free(ptr);
    free(type_array);
}
