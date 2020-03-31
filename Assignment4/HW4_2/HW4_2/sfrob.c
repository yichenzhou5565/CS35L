#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
////Function #1: comparing two c-strings
int frobcmp( char const *a, char const *b);
///Test Cases: for Func #1
///void testFrobcmp();

int compareWordList(const void *a, const void *b);
char frob(char c);



int main()
{
    //testFrobcmp();
    ///Big Idea:
    ///I/O: use getchar() to access the current character
    ///error checking: if EOF then end the process
    
    //create a string, or a char* to contain all characters within a word
    //create a char** array callled wordlist to contain all words
    ///this is really what an array of string class in C++ tend to achieve
    
    ///the idea is really that a data structure like vector in C++ would help
    ///bu unfortunately it seems we do not have such a std data structure in C
    ///so we have to use malloc and reallloc to implment "vector"
    //and we have to set 2 additional variables to keep track of the word size
    //and the list size
    
    char* word = (char*)malloc(sizeof(char));
    char** word_list = (char**)malloc(sizeof(char*));
    
    if (word==NULL || word_list==NULL)
    {
        fprintf(stderr,
                "Unsuccessful dynamic memory ALLOCATION");
        exit(1);
    }
    
    int wordSize=0, listSize=0;
    
    int curChar=getchar();  ///current character
    int nextChar = getchar();
    
    while (curChar != EOF)
    {
        word[wordSize] = (char)curChar;
        char* tempWord = (char*)realloc(word, sizeof(char)*(wordSize+2));
        word = tempWord;
        
        if (tempWord == NULL)
        {
            fprintf(stderr,
                    "Memory Leak due to unsuccessful dynamic memory REALLOCATION.");
            exit(1);
        }
        
        if ((char)curChar == ' ') ///end of the word
        {
            ///now we are ready to put the word into the former created wordlist
            word_list[listSize] = tempWord;
            char** tempList = (char**)realloc(word_list, sizeof(char*)*(listSize+2));
            
            if (tempList == NULL)
            {
                fprintf(stderr,
                        "Memory Leak due to unsuccessful dynamic memory REALLOCATION.");
                exit(1);
            }
            
            word_list = tempList;
            listSize += 1;   //increment size of the wordlist
            
            //            if (word)
            //            {
            //                free(word);
            word = NULL;
            //}
            //free(word);  //free word and allocate again
            word = (char*)malloc(sizeof(char));
            if (word==NULL)
            {
                fprintf(stderr,
                        "Unsuccessful dynamic memory ALLOCATION");
                exit(1);
            }
            wordSize = -1;
            
            while ((char)nextChar==' ')
            {
                curChar = nextChar;
                nextChar = getchar();
            }
            
            wordSize += 1;
            curChar = nextChar;
            nextChar = getchar();
            //continue;
        }
        
//        while ((char)curChar==' ' && (char)nextChar==' ')
//        {
//            //printf("***");
//            curChar = nextChar;
//            nextChar=getchar();
//        }
        
        else if ((char)curChar!=' ' && nextChar==EOF)
        {
            wordSize += 1;
            curChar = (int)' ';
            continue;
        }
        
        else if ((char)curChar==' ' && nextChar==EOF)
        {
            break;
        }
   
        else
        {
            wordSize += 1;
            curChar = nextChar;
            nextChar = getchar();
        }
        
//        wordSize += 1;
//        curChar = nextChar;
//        nextChar = getchar();
    }
    
    ///Now do the sorting
    qsort(word_list, listSize, sizeof(char*), compareWordList);
    
    ///print the sorted thing into std output
    //we choose to use putchar instead of print because
    //we need faster speed as we are expected to handle very big files
    int i;
    for (i=0; i<listSize; i++)
    {
        int j;
        for (j=0;  ;j++)
        {
            putchar(word_list[i][j]);
            if (word_list[i][j]==' ')
            {
                break;
            }
        }
    }
    
    ///Free the dynamically allocated memory
    for (i=0; i<listSize; i++)
    {
        //        if (word_list[i])
        //        {
        free(word_list[i]);
        //}
        
    }
    //    if (word_list)
    //    {
    free(word_list);
    //}
    
    
    return (0);
}

//void testFrobcmp()
//{
//    char* s1="\0A";
//    char* s2="\0AO";
//    assert(frobcmp(s1, s2)<0);
//
//    printf("*****************\n");
//    printf("Passed all tests.\n");
//    printf("*****************\n");
//}


int frobcmp( char const *a, char const *b)
{
    if (a==NULL || b==NULL)
        return INT_MAX;
    for(;;)
    {
        while (*a=='\0')
        {
            a++;
        }
        while (*b=='\0')
        {
            b++;
        }
        
        if (*a==' ' && *b==' ')
        {
            return 0;
        }
        else if (*a==' ' && *b != ' ')
        {
            return -1;
        }
        else if (*a!=' ' && *b == ' ')
        {
            return 1;
        }
        else
        {
            if (frob(*a)>frob(*b))
                return 1;
            if (frob(*a)<frob(*b))
                return -1;
            else
            {
                a++;
                b++;
            }
        }
    }
    return 0;
}


int compareWordList(const void *a, const void *b)
{
    const char* temp1 = *(const char**)a;
    const char* temp2 = *(const char**)b;
    return (frobcmp(temp1, temp2));
}

char frob(char c)
{
    return (c^42);
}

