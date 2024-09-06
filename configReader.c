#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

typedef enum configType {
    CONFIG_STRING,
    CONFIG_INT,
} configType;

typedef struct config_fetch_options {
    char name[MAX_LINE];
    void* value_ptr;
    configType outputType;
} config_fetch_options;

int isEndCharacter(char c)
{
    // 0 is the default charater. It is needed because the last line might not have an end character.
    return c == '\n' || c == '#' || c == ';' || c == 0;
}

void stripWhiteSpace(char* str)
{
    int whiteSpaceAtStart = 0;
    while(str[whiteSpaceAtStart] == ' ') whiteSpaceAtStart++;
    int len = strlen(str);
    int whiteSpaceAtEnd = 0;
    while(str[len - whiteSpaceAtEnd - 1] == ' ') whiteSpaceAtEnd++;

    int newLen = len - whiteSpaceAtStart - whiteSpaceAtEnd;
    for(int i = 0; i < newLen; i++)
    {
        str[i] = str[i+whiteSpaceAtStart];
    }
    memset(str + newLen, 0, len-newLen);
}

void getConfigurations(char* filename, config_fetch_options* options, int optionsCount)
{
    //read config.ini for values
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open %s\n", filename );
        exit(1);
    }

    char line[MAX_LINE];
    int lineNumber = 0;
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        int lineOffset = 0;
        while(lineOffset < MAX_LINE && line[lineOffset] == ' ') lineOffset++;
        if(lineOffset >= MAX_LINE || line[lineOffset] == '\n' || line[lineOffset] =='#' || line[lineOffset] ==';') continue;

        char name[MAX_LINE];
        char value[MAX_LINE];
        memset(name, 0, MAX_LINE);
        memset(value, 0, MAX_LINE);
        int resultOffset = 0;
        int start = 1;
        while(line[lineOffset] != '=')
        {   

            if(isEndCharacter(line[lineOffset]))
            {
                printf("%s line %i is missing =\n", filename, lineNumber);
                exit(1);
            }
            else
            {
                name[resultOffset] = line[lineOffset];
                resultOffset++;
            }
            lineOffset++;
        }
        lineOffset++;
        resultOffset = 0;
        while(!isEndCharacter(line[lineOffset]))
        {
            value[resultOffset] = line[lineOffset];
            resultOffset++;
            lineOffset++;
        }

        stripWhiteSpace(name);
        stripWhiteSpace(value);

        int matchingOptionIndex = -1;
        for(int i = 0; i < optionsCount; i++)
        {
            if(!strcmp(options[i].name, name))
            {
                matchingOptionIndex = i;
                break;
            }
        }
        
        if(matchingOptionIndex == -1)
        {
            printf("%s line %i doesn't match any read option.\n", filename, lineNumber);
        }

        switch (options[matchingOptionIndex].outputType) {
            case CONFIG_STRING:
                strcpy((char*)options[matchingOptionIndex].value_ptr, value);
                break;
            case CONFIG_INT:
                *((int*)options[matchingOptionIndex].value_ptr) = atoi(value);
                break;
        }

        lineNumber++;
    }

    fclose(fp);
}