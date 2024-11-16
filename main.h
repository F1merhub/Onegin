#ifndef main_H
#define main_H

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

int if_in_str(char * str, char c);  // проверка есть ли символ в строке

int my_reverse_strcmp(char* str1, char* str2);

#endif
