#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isIsomorphic(char* s, char* t) {
    if (strlen(s) != strlen(t)) {
        return false;
    }
    
    char mapS[256] = {0};
    char mapT[256] = {0};
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (mapS[s[i]] != 0 && mapS[s[i]] != t[i]) {
            return false;
        }
        
        if (mapT[t[i]] != 0 && mapT[t[i]] != s[i]) {
            return false;
        }
        
        mapS[s[i]] = t[i];
        mapT[t[i]] = s[i];
    }
    
    return true;
}

int main() {
    char s1[] = "egg";
    char t1[] = "add";
    char s2[] = "foo";
    char t2[] = "bar";
    char s3[] = "paper";
    char t3[] = "title";
    
    printf("Test 1: %s\n", isIsomorphic(s1, t1) ? "true" : "false");
    printf("Test 2: %s\n", isIsomorphic(s2, t2) ? "true" : "false");
    printf("Test 3: %s\n", isIsomorphic(s3, t3) ? "true" : "false");
    
    return 0;
}
