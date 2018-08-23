#include <stdlib.h>
#include <stdbool.h>
#include "mediaType.h"
#include <string.h>
#include <ctype.h>

categoryType convertStringToType(char * string)
{
    bool invalidType[TYPES_QTY] = {0};
    categoryType validCategory = ERROR_TYPE;
    size_t invalidQty = 0;
    size_t length = strlen(string) + 1;

    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < TYPES_QTY; j++)
        {
            if(!invalidType[j])
            {
                if(tolower(string[i]) - tolower(categoryTypeTable[j][i]) != 0)
                {
                    invalidType[j] = true;
                    invalidQty++;
                }
                else
                    validCategory = j;
                if(invalidQty == TYPES_QTY)
                    return ERROR_TYPE;
            }
        }
    }

    return validCategory;
}

