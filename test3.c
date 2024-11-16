// првоерка, чтобы не выводились доп символы перевода строки

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main() {
    FILE *file1 = fopen("test1.txt", "w");
    char m[] = {'1', '\r', '\n', '3', '4', '\n'};
    fwrite(m, 1, 6, file1);
    fclose(file1);
    return 0;
}
