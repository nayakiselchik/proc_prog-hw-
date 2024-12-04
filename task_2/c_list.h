#ifndef C_LIST_H
#define C_LIST_H

#include <stddef.h>

typedef enum {
    int_type,
    float_type,
    string_type
} list_data_type;

typedef struct c_list {
    void** items;
    list_data_type* types;
    size_t size;
    size_t capacity;
    
    void (*append)(struct c_list* list, void* item, list_data_type type);
    void (*pop)(struct c_list* list);
    void (*destroy)(struct c_list* list);
    void (*print)(const struct c_list* list);

    void (*remove_item)(struct c_list* list, void* item, list_data_type type);
    void (*sort)(struct c_list* list);
} c_list;

c_list* create_list(size_t initial_capacity);
void append(c_list* list, void* item, list_data_type type);
void pop(c_list* list);
void destroy(c_list* list);
void print_list(const c_list* list);

// variant 3
void remove_item(c_list* list, void* item, list_data_type type);
void sort_list(c_list* list);

#endif
