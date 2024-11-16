#include "main.h"

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

    char **A;
    A = (char**)malloc(sizeof(char*)*line_count);
    A[0] = buffer;
    input(A, buffer, file_size);

    mysort(A, line_count);
    
    for (int i = 0; i < line_count; ++i)
        fputs(A[i], file2);

    fclose(file1);
    fclose(file2);
    free(A);
    free(buffer);
    return 0;
}



