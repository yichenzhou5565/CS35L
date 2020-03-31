#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>



////Function #1: comparing two c-strings
int frobcmp( char const *a, char const *b);
///Test Cases: for Func #1
///void testFrobcmp();

int compareWordList(const void *a, const void *b);
char frob(char c);
bool have_f = false;
int main(int argc, const char* argv[])
{
    //testFrobcmp();
    ///Big Idea for last time:
        ///note that this time we will be making much modifications,
        ///and therefore the below high level algorithm is just for reference
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
    
    ///Error handling for reading, argument counts, and argument contents
    
    off_t fileSize=0;
    struct stat buf;
    //int curChar=0;  ///current character
    //int nextChar=0;
//    char* word = (char*)malloc(sizeof(char));
//    char** word_list = (char**)malloc(sizeof(char*));
    //int wordSize=0, listSize=0;
    
    int i=0;
    char** str_arr=NULL;
    int s_digit = -1;
    bool addStr = true;
    
//    if (word==NULL || word_list==NULL)
//    {
//        write(2,
//              "Unsuccessful dynamic memory ALLOCATION.\n", 40);
//        exit(1);
//    }
    
    if ( fstat(0, &buf) < 0 )  ///signals failure of system call
    {
        write(2, "Error in reading the file.\n", 26);
        exit(1);
    }

    if (argc > 2)   ///invalid number of operands
    {
        write(2, "Too many operands.\n", 19);
        exit(1);
    }
    else if (argc == 2)   ///if number of operands valid, go on checking..
    {
        if (argv[1][0] != '-' || argv[1][1] != 'f')   ///chech for -f flag
        {
            write(2, "The second operand is invalid.\n", 30);
            exit(1);
        }
        else
        {
            have_f = true;
        }
    }
    
    char *file=NULL;
    if (S_ISREG(buf.st_mode))  ///check for regular file
    {
        //printf("****#");
        fileSize = buf.st_size;
        file = (char*)malloc(sizeof(char) * (fileSize+1));
        if (read(0, file, fileSize) < 0)
        {
            write(2, "Error in System Calls.\n", 23);
            exit(1);
        }
        
        int wc_file=0;  ///keep track of the word counts in the file, for future uses
        
        for (i=0; i<fileSize; i++)   ///get word count
        {
            if (i==0 && file[i]!=' ')
            {
                wc_file += 1;
            }
            if (file[i]==' ')
            {
                while (file[i]==' '&& i<=fileSize-1)
                {
                    i++;
                }
                if(i<fileSize)
                {
                    wc_file += 1;
                }
            }
        }
        
        
        file[fileSize] = ' ';    ///add a trailing space at the end of the file
        
        str_arr = (char**)malloc(sizeof(char*) * (wc_file));
        if (str_arr==NULL)    ///error handling for malloc
        {
            write(2, "Unsuccessful allocation for str_arr.\n", 37);
            exit(1);
        }
        
        for (i=0; i<fileSize; i++)
        {
            if (addStr==true && file[i]!=' ')  ///if not the end of word
            {
                s_digit += 1 ;
                addStr = false;
                str_arr[s_digit] = &file[i];
            }
            if (addStr==false && file[i]==' ')  ///signals the end of the word
            {
                addStr = true; ///go on to the next word...
            }
        }
    }
    
    
    else  ///if not a regular file, then just,
                ///well, do the dynamiclly allocation char by char
    {
        str_arr = (char**)malloc(sizeof(char*));
        if (str_arr==NULL)   ///error handling for str_arr
        {
            write(2, "Unsuccessful allocation for str_arr.\n", 37);
            exit(1);
        }
    }
    
    char* str ;
    char input[1];
    char ch;
    int ch_digit=0;
    
    for(;;)  ///infinite loop
    {
        int fd = read(0, input, 1); ///read input
        if (fd<1)
            break;  ///reaching end of file
        ch = input[0];
        if (addStr==false)
        {
            str = (char*)realloc(str, sizeof(char) * (ch_digit+1));
            if (str==NULL) ///error handling for str
            {
                write(2, "Unsuccessful allocation for str.\n", 33);
                exit(1);
            }
            str[ch_digit] = ch; ///this is (almost) the same as last time's
            str_arr[s_digit] = str;
            ch_digit += 1;
            
            if (ch == ' ')
            {
                addStr = true;
            }
        }
        
        else
        {
            ch_digit = 0;
            if (ch == ' ' && ch_digit==0)  ///consecutive space
                continue;
            s_digit += 1;
            str_arr = (char**)realloc(str_arr, sizeof(char*) * (s_digit+1));
            if (str_arr==NULL) ///error handling for str_arr
            {
                write(2, "Unsuccessful allocation for str_arr.\n", 37);
                exit(1);
            }
            str = (char*)malloc(sizeof(char));
            if (str==NULL)   ///error handing for str
            {
                write(2, "Unsuccessful allocation for str.\n", 33);
                exit(1);
            }
            addStr = false;  ///update variables
            str[ch_digit] = ch;
            ch_digit += 1;
            str_arr[s_digit] = str;
        }
    }
    
    ///append space to end of the file if necessary
    if (s_digit!=-1  &&  str_arr[s_digit][ch_digit-1]!=' ')
    {
        str = (char*)realloc(str, sizeof(char) * (ch_digit+1));
        if (str==NULL)
        {
            write(2, "Unsuccessful allocation for str.\n", 33);
            exit(1);
        }
        str[ch_digit] = ' ';
        str_arr[s_digit] = str;
    }
    
    ///Now do the sorting
    qsort(str_arr, s_digit+1 , sizeof(char*), compareWordList);
    
    ///print the sorted thing into std output
    //we choose to use putchar instead of print because
    //we need faster speed as we are expected to handle very big files
    //int i;
    int j;
    char helper[1];
    for (i=0; i<s_digit+1; i++)
    {
        for (j=0;  ;j++)
        {
            helper[0] = str_arr[i][j];
            write(1, helper, 1);
            //            while (word_list[i][j]!=' ')
            //            {
            //                write(1, &word_list[i][j], 1);
            //            }
            if (str_arr[i][j]==' ')
                break;
        }
        if (S_ISREG(buf.st_mode)==false)
            free(str_arr[i]);
    }
    
    
    
    ///Free the dynamically allocated memory
    if (S_ISREG(buf.st_mode)==true)
    {
        free(file);
    }
    
    if (str_arr != NULL)
        free(str_arr);
    
    
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
            if (have_f==false)
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
            else
            {
                if (toupper((unsigned char)frob(*a))>toupper((unsigned char)frob(*b)))
                    return 1;
                if (toupper((unsigned char)frob(*a))<toupper((unsigned char)frob(*b)))
                    return -1;
                else
                {
                    a++;
                    b++;
                }
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


