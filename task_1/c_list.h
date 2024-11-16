#ifndef C_LIST_H
#define C_LIST_H
#define CAPACITY 100
// Enum to identify the data type
typedef enum {
int_type,
float_type,
string_type
} list_data_type;
/**
* @brief Adds an item to the list.
*
* This function appends an element of any type (int, float, string) to
the list,
* and also keeps track of the type for later retrieval and display.
*
* @param list[] An array of pointers that represents the list to which
the item will be added.
* @param size The current size of the list.
* @param item A pointer to the item that will be added to the list.
* @param type The data type of the item being added (int, float, or
string).
*
* @return The new size of the list if the item is added successfully,
or -1 if the list is full.
*/
int append_list_item(void* list[], int size, void* item, list_data_type
type);
/**
* @brief Prints the elements of the list.
*
* This function iterates through the list and prints each element based
on its stored type (int, float, or string).
* It uses the list_types array to determine the data type of each
element and casts the pointer accordingly for printing.
*
* @param list[] An array of pointers representing the list elements.
* @param size The number of elements in the list.
*/
void print_list(const void* list[], int size);
#endif // C_LIST_H