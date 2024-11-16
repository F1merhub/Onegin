#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void mysort(char **A, int line_count);  //  сортирует пузырьком массив указателей на строки

int my_strcmp(char* str1, char* str2);

void input(char **A, char *buffer, int file_size);

void find_size(long * file_size, FILE * file1);

void find_line_count(int *line_count, long file_size, char * buffer);

void print_not_sort_file(long file_size, int line_count, char * buffer, FILE * file1, FILE * file2);

int main()
{
    FILE *file1 = fopen("test1.txt", "rb");
    FILE *file2 = fopen("test2.txt", "wb");

    if (!file1)
    {
        printf("text from test1.txt does not exist\n");
        return -1;
    }

    long file_size = 0;
    find_size(&file_size, file1);

    char *buffer;
    buffer = (char*)malloc(file_size * sizeof(char));
    if (buffer == NULL)
    {
        printf("ERROR of working malloc: buffer == NULL\n");
            free(buffer);
            fclose(file1);
            return -1;

    }
    
    fread(buffer, 1, file_size, file1);

    int line_count = 0;
    find_line_count(&line_count, file_size, buffer);

    print_not_sort_file(file_size, line_count, buffer, file1, file2);

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

void find_size(long * file_size, FILE * file1) {
    fseek(file1, 0, SEEK_END);
    *file_size = ftell(file1);
    fseek(file1, 0, SEEK_SET);
}

void find_line_count(int *line_count, long file_size, char * buffer) {
    for (int i = 0; i < file_size; ++i) {
        if (buffer[i] == '\n')
            (*line_count)++;
    }
}

void print_not_sort_file(long file_size, int line_count, char * buffer, FILE * file1, FILE * file2) {

    char text1[] = "*****TEXT BEFORE SORT*****\n\n";
    char text2[] = "\n*****TEXT AFTER SORT*****\n\n";
    int k = 0;
    char buffer_for_repeat[file_size - line_count + 1] = {};

    for (int i = 0; i < file_size - line_count; i++) {
        if (buffer[i] != '\r')
            buffer_for_repeat[i] = buffer[i + k];
        else
        {
            k++;
            buffer_for_repeat[i] = buffer[i + k];
        }
    }

    buffer_for_repeat[file_size - line_count] = '\n';
    fputs(text1, file2);
    fwrite(buffer_for_repeat, 1, file_size - line_count + 1, file2);
    fputs(text2, file2);

}
