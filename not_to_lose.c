int my_strcmp(char* str1, char* str2) {
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



