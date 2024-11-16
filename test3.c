#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int if_in_str(char * str, char c) {
    int i = 0;
    int flag = 0;
    while(str[i]) {
        if  (str[i] == c)
            flag = 1;
        i++;
    }
    return flag;
}

int my_strcmp(char* str1, char* str2) {
    int i1 = 0;
    int i2 = 0;
    char A[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (str1[i1] && str2[i2]) {

        if (if_in_str(A, str1[i1]) && if_in_str(A, str2[i2]))
        {
            printf("%d %d", if_in_str(A, str1[i1]), if_in_str(A, str2[i2]));
            if (str1[i1] != str2[i2])
                break;
            i1++;
            i2++;
        }
        else
        {
            if (!if_in_str(A, str1[i1]))
                i1++;
            if (!if_in_str(A, str2[i2]))
                i2++;
        }
    }
    return str1[i1] - str2[i2];
}



int main() {
    char str1[] = "3";
    char str2[] = "6";
    my_strcmp(str1, str2);
    //printf("%d", my_strcmp(str1, str2));
    return 0;
}
