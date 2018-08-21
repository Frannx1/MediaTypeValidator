#include <stdlib.h>
#include <stdbool.h>
#include "mediaType.h"
#include <string.h>
#include <ctype.h>

cathegoryType convertStringToType(char * string)
{
    bool invalidType[TYPES_QTY] = {0};
    cathegoryType validCategory;
    size_t invalidQty = 0;
    size_t length = strlen(string) + 1;

    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < TYPES_QTY; j++)
        {
            if(!invalidType[j])
            {
                if(tolower(string[i]) - tolower(cathegoryTypeTable[j][i]) != 0)
                {
                    invalidType[j] = true;
                    invalidQty++;
                }
                if(invalidQty == TYPES_QTY)
                    return ERROR;
                validCategory = j;
            }
        }
    }
    
    return validCategory;
}

