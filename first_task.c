#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

char encrypt_char(char ch, int key) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return (ch - base + key + 26) % 26 + base;
    }
    return ch; 
}

void encrypt_string(char *input, int key, char *output) {
    for (int i = 0; input[i] != '\0'; i++) {
        output[i] = encrypt_char(input[i], key);
    }
    output[strlen(input)] = '\0';
}

int break_caesar_cipher(char *encrypted) {
    int frequency[26] = {0};
    
    for (int i = 0; encrypted[i] != '\0'; i++) {
        if (isalpha(encrypted[i])) {
            char lower = tolower(encrypted[i]);
            frequency[lower - 'a']++;
        }
    }

    int max_index = 0;
    for (int i = 1; i < 26; i++) {
        if (frequency[i] > frequency[max_index]) {
            max_index = i;
        }
    }


    int key = (max_index - (4 + 26)) % 26;
    return key < 0 ? key + 26 : key;
}

int main() {
    char input[MAX_LENGTH];
    char encrypted[MAX_LENGTH];
    int key;

    printf("Enter a normal English string (up to 100 characters): ");
    fgets(input, MAX_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter the encryption key: ");
    scanf("%d", &key);

    encrypt_string(input, key, encrypted);
    printf("Encrypted string: %s\n", encrypted);

    int decrypted_key = break_caesar_cipher(encrypted);
    printf("Decrypted key: %d\n", decrypted_key);

    return 0;
}
