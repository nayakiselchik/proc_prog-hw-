#include <stdio.h>

int main() {
    int value, key;
    
    printf("Enter a value: ");
    scanf("%d", &value);
    
    printf("Enter a key: ");
    scanf("%d", &key);

    printf("Original: %d\n", value);
    
    int encrypted_value = value ^ key;
    printf("Encrypted: %d\n", encrypted_value);
    
    int decrypted_value = encrypted_value ^ key;
    printf("Decrypted: %d\n", decrypted_value);
    
    return 0;
}
