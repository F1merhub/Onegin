#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int my_reverse_strcmp(char* str1, char* str2) {
    int i = strlen(str1);
    int j = strlen(str2);
    while (i >= 0 && j >= 0) {
        if (str1[i] != str2[j])
            break;
        i--;
        j--;
    }
    return str1[i] - str2[i];
}

int main() {
    char str1[] = "aaaab";
    char str2[] = "bbbba";
    int x = my_strcmp(str1, str2);
    printf("%d", x);
    return 0;
}


