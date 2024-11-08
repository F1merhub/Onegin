#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void mysort(char **A, int line_count);  //  сортирует пузырьком массив указателей на строки

int my_strcmp(char* str1, char* str2);

void input(char **A, char *buffer, int file_size);

int main()
{
    FILE *file1 = fopen("test1.txt", "rb");

    fseek(file1, 0, SEEK_END);
    long file_size = ftell(file1);
    fseek(file1, 0, SEEK_SET);

    char *buffer;
    buffer = (char*)malloc(file_size * sizeof(char));
    fread(buffer, 1, file_size, file1);

    FILE *file2 = fopen("test2.txt", "w");
    fwrite(buffer, 1, file_size, file2);

    int line_count = 0;
    for (int i = 0; i < file_size; ++i) {
        if (buffer[i] == '\n')
            line_count++;
    }

    char **A;                                           //
    A = (char**)malloc(sizeof(char*)*line_count);       // расставляем указатели в массиве A
    A[0] = buffer;                                      //
    input(A, buffer, file_size);                        //

    mysort(A, line_count);                  //
    for (int i = 0; i < line_count; ++i)    // сортируем буффер и выводим в файл
        fputs(A[i], file2);                 //

    fclose(file1);
    fclose(file2);
    free(A);
    free(buffer);
    return 0;
}


int my_strcmp(char* str1, char* str2) {
    int i = 0;
    while (str1[i] && str2[i]) {
        if (str1[i] != str2[i])
            break;
        i++;
    }
    return str1[i] - str2[i];
}


void mysort(char **A, int line_count) {
    for (int i = line_count-1; i>=0; i--){
        for (int j = 0;j<i; j++) {
            if (my_strcmp(A[j], A[j+1]) > 0) {
                char *buffer = A[j];
                A[j] = A[j+1];
                A[j+1] = buffer;
            }
        }
    }
}


void input(char **A, char *buffer, int file_size) {
    int j = 1;
    for (int i = 0; i < file_size; ++i) {
        if (buffer[i] == '\n') {
            buffer[i-1] = '\n';
            buffer[i] = '\0';
            if (i != file_size - 1) {
                A[j] = (char*)(&(buffer[i + 1]));
                j++;
            }
            else
                break;
        }
        assert((i >= 0) && (i < file_size));
    }
}
