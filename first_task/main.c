#include <stdio.h>
#include "c_list.h"

int main() {
    int size = 0;
    void** list = create();
    if (!list) {
        printf("Failed to create list.\n");
        return 1;
    }

    int int_value = -6;
    list = append(list, &size, &int_value, int_type);

    float float_value = 0.1f;
    list = append(list, &size, &float_value, float_type);

    char* string_value = "string_type";
    list = append(list, &size, string_value, string_type);

    printf("Original list:\n");
    print((const void**)list, size);

    list = pop(list, &size);
    printf("List after pop:\n");
    print((const void**)list, size);

    destroy(list);
    return 0;
}
