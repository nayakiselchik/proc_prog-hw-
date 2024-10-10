#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MIN_KEY -256
#define MAX_KEY 256

char encrypt(char ch, int key) {
    ch = tolower(ch);
    if (isalpha(ch)) {
        return ((ch - 'a' + key) % 26 + 26) % 26 + 'a';
    }
    return ch;
}

int main() {
    int num_chars, key;
    char ch;

    printf("Enter the number of characters to encrypt: ");
    if (scanf("%d", &num_chars) != 1 || num_chars <= 0) {
        printf("Invalid input: must be a positive integer\n");
        return 1;
    }

    srand(time(0));
    key = (rand() % (MAX_KEY - MIN_KEY + 1)) + MIN_KEY;
    printf("Generated encryption key: %d\n", key);


    for (int i = 0; i < num_chars; i++) {
        printf("Enter character %d: ", i + 1);
        scanf(" %c", &ch);

        if (isalpha(ch)) {
            char encrypted_char = encrypt(ch, key);
            printf("Encrypted character: %c\n", encrypted_char);
        } else {
            printf("Invalid input: must be a valid alphabetic character\n");
            i--;
        }
    }

    return 0;
}
