#include "c_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static c_list* sort_list_ctx = NULL;

static void resize_if_needed(c_list* list) {
    if (list->size >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        void** new_items = realloc(list->items, new_capacity * sizeof(void*));
        list_data_type* new_types = realloc(list->types, new_capacity * sizeof(list_data_type));
        if (!new_items || !new_types) {
            fprintf(stderr, "Memory allocation failed during resize.\n");
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
        list->types = new_types;
        list->capacity = new_capacity;
    }
}

c_list* create_list(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 4;
    }

    c_list* list = (c_list*)malloc(sizeof(c_list));
    if (!list) {
        fprintf(stderr, "Memory allocation failed for list.\n");
        exit(EXIT_FAILURE);
    }

    list->items = (void**)malloc(initial_capacity * sizeof(void*));
    list->types = (list_data_type*)malloc(initial_capacity * sizeof(list_data_type));
    if (!list->items || !list->types) {
        fprintf(stderr, "Memory allocation failed for items or types.\n");
        free(list->items);
        free(list->types);
        free(list);
        exit(EXIT_FAILURE);
    }

    list->size = 0;
    list->capacity = initial_capacity;

    list->append = append;
    list->pop = pop;
    list->destroy = destroy;
    list->print = print_list;

    list->remove_item = remove_item;
    list->sort = sort_list;

    return list;
}

void append(c_list* list, void* item, list_data_type type) {
    assert(list != NULL);
    resize_if_needed(list);
    if (type == string_type) {
        char* copy = strdup((char*)item);
        if (!copy) {
            fprintf(stderr, "Memory allocation failed for string copy.\n");
            exit(EXIT_FAILURE);
        }
        list->items[list->size] = copy;
    } else {
        if (type == int_type) {
            int* val = (int*)malloc(sizeof(int));
            if (!val) {
                fprintf(stderr, "Memory allocation failed for int.\n");
                exit(EXIT_FAILURE);
            }
            *val = *((int*)item);
            list->items[list->size] = val;
        } else {
            float* val = (float*)malloc(sizeof(float));
            if (!val) {
                fprintf(stderr, "Memory allocation failed for float.\n");
                exit(EXIT_FAILURE);
            }
            *val = *((float*)item);
            list->items[list->size] = val;
        }
    }

    list->types[list->size] = type;
    list->size++;
}

void pop(c_list* list) {
    assert(list != NULL);
    if (list->size == 0) {
        return;
    }

    size_t idx = list->size - 1;
    if (list->types[idx] == int_type || list->types[idx] == float_type || list->types[idx] == string_type) {
        free(list->items[idx]);
    }

    list->size--;
}

void destroy(c_list* list) {
    if (!list) return;
    for (size_t i = 0; i < list->size; i++) {
        free(list->items[i]);
    }
    free(list->items);
    free(list->types);
    free(list);
}

void print_list(const c_list* list) {
    assert(list != NULL);
    printf("[");
    for (size_t i = 0; i < list->size; i++) {
        if (list->types[i] == int_type) {
            printf("%d", *((int*)list->items[i]));
        } else if (list->types[i] == float_type) {
            printf("%.2f", *((float*)list->items[i]));
        } else if (list->types[i] == string_type) {
            printf("\"%s\"", (char*)list->items[i]);
        }
        if (i < list->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// variant 3

void remove_item(c_list* list, void* item, list_data_type type) {
    assert(list != NULL);

    for (size_t i = 0; i < list->size; i++) {
        int found = 0;
        if (list->types[i] == type) {
            if (type == int_type) {
                if (*((int*)list->items[i]) == *((int*)item)) {
                    found = 1;
                }
            } else if (type == float_type) {
                if (*((float*)list->items[i]) == *((float*)item)) {
                    found = 1;
                }
            } else if (type == string_type) {
                if (strcmp((char*)list->items[i], (char*)item) == 0) {
                    found = 1;
                }
            }
        }
        if (found) {
            free(list->items[i]);
            for (size_t j = i; j < list->size - 1; j++) {
                list->items[j] = list->items[j+1];
                list->types[j] = list->types[j+1];
            }
            list->size--;
            return;
        }
    }
}

static int compare_wrapper(const void* a, const void* b) {
    size_t a_idx = *((size_t*)a);
    size_t b_idx = *((size_t*)b);

    list_data_type type_a = sort_list_ctx->types[a_idx];
    list_data_type type_b = sort_list_ctx->types[b_idx];

    if (type_a != type_b) {
        return (int)type_a - (int)type_b;
    }

    if (type_a == int_type) {
        int val_a = *((int*)sort_list_ctx->items[a_idx]);
        int val_b = *((int*)sort_list_ctx->items[b_idx]);
        return val_a - val_b;
    } else if (type_a == float_type) {
        float val_a = *((float*)sort_list_ctx->items[a_idx]);
        float val_b = *((float*)sort_list_ctx->items[b_idx]);
        return (val_a > val_b) - (val_a < val_b);
    } else {
        char* str_a = (char*)sort_list_ctx->items[a_idx];
        char* str_b = (char*)sort_list_ctx->items[b_idx];
        return strcmp(str_a, str_b);
    }
}

void sort_list(c_list* list) {
    assert(list != NULL);
    if (list->size < 2) {
        return;
    }

    sort_list_ctx = list;

    size_t* indices = (size_t*)malloc(list->size * sizeof(size_t));
    if (!indices) {
        fprintf(stderr, "Memory allocation failed in sort.\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < list->size; i++) {
        indices[i] = i;
    }

    qsort(indices, list->size, sizeof(size_t), compare_wrapper);

    void** new_items = (void**)malloc(list->size * sizeof(void*));
    list_data_type* new_types = (list_data_type*)malloc(list->size * sizeof(list_data_type));
    if (!new_items || !new_types) {
        fprintf(stderr, "Memory allocation failed during sort rearrangement.\n");
        free(indices);
        free(new_items);
        free(new_types);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < list->size; i++) {
        new_items[i] = list->items[indices[i]];
        new_types[i] = list->types[indices[i]];
    }

    free(list->items);
    free(list->types);
    list->items = new_items;
    list->types = new_types;

    free(indices);
    sort_list_ctx = NULL;
}
