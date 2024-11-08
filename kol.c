#include <stdio.h>
#include <assert.h>
#include <malloc.h>


struct DataText{

    int text_size;
    int number_of_lines;
    int* strings_len;
    char** strings;
    char* buffer;
};

void GetSizeOfFile( int* text_size, FILE* fonegin);
void ReadText( DataText* main_text );
void MakeBuffer( DataText* main_text );
void GetStrings( DataText* main_text );
void InputToBuffer( DataText* main_text , FILE* fonegin);
void WriteText( DataText* const main_text );
void BubbleSort( DataText* main_text);

int main()
{
    DataText main_text = {};
    ReadText( &main_text );
    WriteText( &main_text );

    return 0;
}

void ReadText( DataText* main_text )
{
    assert( main_text != NULL );

    MakeBuffer( main_text );

    GetStrings( main_text );
}

void MakeBuffer( DataText* main_text )
{
    FILE* fonegin = fopen( "text.txt" , "rb" );

    GetSizeOfFile( &(main_text -> text_size), fonegin );
    InputToBuffer( main_text , fonegin);

    fclose( fonegin );
}

void GetSizeOfFile( int* text_size, FILE* fonegin)
{
    assert( text_size != NULL);

    fseek( fonegin, 0 , SEEK_END );
    *text_size = ftell( fonegin );
}


void GetStrings( DataText* main_text )
{
    assert( main_text != NULL );

    int count_lines = 1;

    for( int i = 0; i < (main_text -> text_size); i++ )
    {
        if( (main_text -> buffer)[i] == '\n')
            count_lines ++;
    }
    //printf("%d\n", count_lines);

    main_text -> number_of_lines = count_lines;
    main_text -> strings = (char**)calloc( count_lines, sizeof(char*) );
    main_text -> strings_len = (int*)calloc( count_lines, sizeof(int));
    main_text -> strings[0] = main_text -> buffer;

    int st_num = 1;

    for( int i = 0; i < (main_text -> text_size); i++ )
    {
        (main_text -> strings_len)[st_num - 1]++;
        if( (main_text -> buffer)[i] == '\n')
        {
            printf("%d\n", (main_text -> strings_len)[st_num - 1]);
            main_text -> strings[st_num] = &( (main_text -> buffer)[i + 1] );
            st_num++;
        }

    }
}

void InputToBuffer( DataText* main_text, FILE* fonegin )
{
    main_text -> buffer = ( char* )calloc( (main_text -> text_size) + 2, sizeof(char) );
    fseek( fonegin, 0 , SEEK_SET );
    fread( main_text -> buffer, sizeof(char), main_text -> text_size, fonegin );
}

void BubbleSort( DataText* main_text)
{

}

void WriteText( DataText* const main_text )
{
    FILE* sort_fonegin = fopen( "sort_text.txt", "w");
    for(int i = 0; i < main_text -> number_of_lines; i++)
    {
        for(int j = 0; j < (main_text -> strings_len)[i]; j++)
            fprintf(sort_fonegin, "%c", (main_text ->strings)[i][j]);
    }

    fclose( sort_fonegin );
}
