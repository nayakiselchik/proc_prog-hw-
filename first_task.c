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
    char input[101]; // Array to hold the input string (max 100 characters + null terminator)
    int key, freq[ALPHABET_SIZE] = {0}; // Frequency array for letters
    char most_common_char;
    int most_common_freq = 0;

    // Input: normal English string
    printf("Enter a normal English string (up to 100 characters): ");
    fgets(input, sizeof(input), stdin);
    
    // Input: encryption key
    printf("Enter the encryption key (as an integer): ");
    scanf("%d", &key);

    // Encrypt the input string
    char encrypted[101]; // Array to hold the encrypted string
    for (int i = 0; i < strlen(input); i++) {
        encrypted[i] = encrypt(input[i], key);
        // Count frequency of letters
        if (isalpha(encrypted[i])) {
            freq[tolower(encrypted[i]) - 'a']++;
        }
    }
    encrypted[strlen(input)] = '\0'; // Null terminate the encrypted string

    // Find the most common letter in the encrypted string
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > most_common_freq) {
            most_common_freq = freq[i];
            most_common_char = i + 'a';
        }
    }

    // Calculate the decryption key
    int decrypted_key = (most_common_char - 'e' + ALPHABET_SIZE) % ALPHABET_SIZE;

    // Output: Decrypted encryption key
    printf("The decryption key is: %d\n", decrypted_key);

    // Evaluate time and space complexity
    printf("Time Complexity: O(n), where n is the length of the input string.\n");
    printf("Space Complexity: O(1) for the frequency array.\n");

    return 0;
}
