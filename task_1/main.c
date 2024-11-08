#include "c_list.h"
#include <stdio.h>
#include <assert.h>
int main() {
void* list[CAPACITY]; // Array to store items
int size = 0; // Current size of the array
int i = 42;
float f = 3.14;
char* s1 = "C programming";
char* s2 = "Home task 6";
size = append_list_item(list, size, &i, int_type); // Add an int_type
size = append_list_item(list, size, &f, float_type); // Add a float
size = append_list_item(list, size, s1, string_type); // Add a string_type
size = append_list_item(list, size, s2, string_type); // Add a string_type
print_list((const void**)list, size); // Print the elements
return 0;
}
