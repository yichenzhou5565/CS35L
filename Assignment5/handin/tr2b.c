#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
    const char* from = argv[1];
    const char* to = argv[2];
    
    ///Error handling:
    
    ///If are of different length
    if (strlen(from) != strlen(to))
    {
        //printf("%d\n  %d\n", strlen(from), strlen(to));
        fprintf(stderr, "Different strlen NOT allowed.\n");
        exit(1);
    }
    
    ///If # of operands is not correct
    if (argc != 3)
    {
        fprintf(stderr, "Number of arguments incorrect.\n");
        exit(1);
    }
    
    ///If from has duplicate bytes
    char helper[1000];
    int i;
    for (i=0; i<1000; i++)
    {
        helper[i] = '\0';   ///helper is really what we have for map in C++
    }
    for (i=0; i<strlen(from); i++)
    {
        int i_from_char = (int)from[i];
        if (helper[i_from_char] != '\0')
        {
            fprintf(stderr, "Duplicates in FROM.\n");
            exit(1);
        }
        else
        {
            helper[i_from_char] = to[i];
        }
    }
    
    ///Translation Process:
    int curChar = getchar();
    while (curChar != EOF)
    {
        if ( helper[curChar] == '\0')
        {
            putchar((char)curChar);
        }
        else
        {
            putchar((char)helper[curChar]);
        }
        curChar = getchar();
    }
    
    return 0;
}
