#include "c_list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
    c_list* list = create_list(2);
    assert(list != NULL);
    assert(list->size == 0);
    assert(list->capacity == 2);

    int x = 10;
    list->append(list, &x, int_type);
    assert(list->size == 1);

    float y = 3.14f;
    list->append(list, &y, float_type);
    assert(list->size == 2);

    char* str = "hello";
    list->append(list, str, string_type);
    assert(list->size == 3);

    list->pop(list);
    assert(list->size == 2);

    float val_to_remove = 3.14f;
    list->remove_item(list, &val_to_remove, float_type);
    assert(list->size == 1);
    assert(list->types[0] == int_type);
    assert(*((int*)list->items[0]) == 10);

    int a = 5;
    int b = 20;
    char* s2 = "apple";
    char* s3 = "banana";
    float f1 = 1.1f;
    float f2 = 2.2f;

    list->append(list, &b, int_type);     // 10, 20
    list->append(list, &a, int_type);     // 10, 20, 5
    list->append(list, &f1, float_type);  // 10, 20, 5, 1.1
    list->append(list, &f2, float_type);  // 10, 20, 5, 1.1, 2.2
    list->append(list, s2, string_type);  // 10,20,5,1.1,2.2,"apple"
    list->append(list, s3, string_type);  // 10,20,5,1.1,2.2,"apple","banana"

    assert(list->size == 7);

    list->sort(list);

    assert(list->size == 7);

    assert(list->types[0] == int_type && *((int*)list->items[0]) == 5);
    assert(list->types[1] == int_type && *((int*)list->items[1]) == 10);
    assert(list->types[2] == int_type && *((int*)list->items[2]) == 20);
    assert(list->types[3] == float_type && *((float*)list->items[3]) == 1.1f);
    assert(list->types[4] == float_type && *((float*)list->items[4]) == 2.2f);
    assert(list->types[5] == string_type && strcmp((char*)list->items[5], "apple") == 0);
    assert(list->types[6] == string_type && strcmp((char*)list->items[6], "banana") == 0);

    list->destroy(list);

    printf("All tests passed!\n");
    return 0;
}
