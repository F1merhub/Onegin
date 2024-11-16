#include "main.h"

int my_strcmp(char* str1, char* str2) {   // Сортировка без символов
    int i1 = 0;
    int i2 = 0;
    char A[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (str1[i1] && str2[i2]) {

        if (if_in_str(A, str1[i1]) && if_in_str(A, str2[i2]))
        {
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


void mysort(char **A, int line_count) {   // сортировка пузырьком
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


void input(char **A, char *buffer, int file_size) {   // обработка буфера
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

void find_size(long * file_size, FILE * file1) {  // поиск размера файла
    fseek(file1, 0, SEEK_END);
    *file_size = ftell(file1);
    fseek(file1, 0, SEEK_SET);
}

void find_line_count(int *line_count, long file_size, char * buffer) {  // поиск кол-ва строк
    for (int i = 0; i < file_size; ++i) {
        if (buffer[i] == '\n')
            (*line_count)++;
    }
}

void print_not_sort_file(long file_size, int line_count, char * buffer, FILE * file1, FILE * file2) {  // вывод изначального файла

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

int if_in_str(char * str, char c) {  // проверка на нахождение символа в строке
    int i = 0;
    int flag = 0;
    while(str[i]) {
        if  (str[i] == c)
            flag = 1;
        i++;
    }
    return flag;
}

int my_reverse_strcmp(char* str1, char* str2) {  // обратная сортировка
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
