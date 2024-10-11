#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define MIN_KEY -256
#define MAX_KEY 256
#define ALPHABET_SIZE 26

char encrypt(char ch, int key) {
    ch = tolower(ch);
    if (isalpha(ch)) {
        return ((ch - 'a' + key) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
    }
    return ch;
}

int main() {
    char input[101];
    int key, freq[ALPHABET_SIZE] = {0};
    char most_common_char;
    int most_common_freq = 0;

    printf("Enter a normal English string (up to 100 characters): ");
    fgets(input, sizeof(input), stdin);
    
    // Input: encryption key
    printf("Enter the encryption key (as an integer): ");
    scanf("%d", &key);

    char encrypted[101];
    for (int i = 0; i < strlen(input); i++) {
        encrypted[i] = encrypt(input[i], key);
        if (isalpha(encrypted[i])) {
            freq[tolower(encrypted[i]) - 'a']++;
        }
    }
    encrypted[strlen(input)] = '\0'; 


    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > most_common_freq) {
            most_common_freq = freq[i];
            most_common_char = i + 'a';
        }
    }


    int decrypted_key = (most_common_char - 'e' + ALPHABET_SIZE) % ALPHABET_SIZE;


    printf("The decryption key is: %d\n", decrypted_key);


    printf("Time Complexity: O(n), where n is the length of the input string.\n");
    printf("Space Complexity: O(1) for the frequency array.\n");

    return 0;
}