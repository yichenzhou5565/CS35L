//
//  main.c
//  tr2u_1
//
//  Created by Yichen Zhou on 10/29/19.
//  Copyright © 2019 Yichen Zhou. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
    const char* from = argv[1];
    const char* to = argv[2];
    //printf("%d\n", "strlen(Different strlen NOT allowed.\n");
    ///Error handling:
    
    ///If are of different length
    if (strlen(from) != strlen(to))
    {
        write(2, "Different strlen NOT allowed.\n", 29);
        //fprintf(stderr, "Different strlen NOT allowed.\n");
        exit(1);
    }
    
    ///If # of operands is not correct
    if (argc != 3)
    {
        write(2, "Number of arguments incorrect.\n", 31);
        //fprintf(stderr, "Number of arguments incorrect.\n");
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
            write(2, "Duplicates in FROM.\n", 20);
            //fprintf(stderr, "Duplicates in FROM.\n");
            exit(1);
        }
        else
        {
            helper[i_from_char] = to[i];
        }
    }
    
    ///Translation Process:
    char curChar[1] ;
    
    while (read(0, curChar, 1) > 0)
    {
        
        if ( helper[(int)curChar[0]] == '\0')
        {
            write(1, curChar, 1);
            //putchar((char)curChar);
        }
        else
        {
            *curChar = helper[(int)curChar[0]];
            write(1, curChar, 1);
            //putchar((char)helper[curChar]);
        }
        //curChar = getchar();
    }
    
    return 0;
}

