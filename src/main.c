#include <stdio.h>
#include <stdlib.h>
#include "errorslib.h"
#include "stringlib.h"
#include "mediaRange.h"
#include "mediaTypeParser.h"


#define BUFFER_LENGTH 256

#define CLEAN_BUFFER { int MACc; while ((MACc = getchar()) != '\n' && MACc != EOF); }


void parseAndMapMediaTypes(mediaRangeADT mediaRange, char ** input, const size_t qty);

void readAndValidateMediaTypes(const mediaRangeADT mediaRange);


int main(int argc, char * argv[])
{
    checkAreEquals(argc, 2, "Invalid Arguments.");
    size_t qty = 0;
    char ** splitedInput = splitString(argv[1], &qty, ',');
    
    mediaRangeADT mediaRange = createMediaRange();
    parseAndMapMediaTypes(mediaRange, splitedInput, qty);
    freeSplitedString(splitedInput, qty);

    readAndValidateMediaTypes(mediaRange);
    deleteMediaRange(mediaRange);
    return 0;
}

void parseAndMapMediaTypes(mediaRangeADT mediaRange, char ** input, const size_t qty)
{
    for (int i = 0; i < qty; i++)
    {
        mediaType mt;
        char * msg = parseToMediaType(input[i], &mt);
        checkAreNotEqualsWithMsgs(mt.type, ERROR_TYPE, 
                "Not valid media-type format inserted in the media-range.", msg);
        addMediaType(mediaRange, mt);
    }
}

void readAndValidateMediaTypes(const mediaRangeADT mediaRange)
{
    char buffer[BUFFER_LENGTH];
    mediaType mt;
    while(1)
    {
        scanf("%256s", buffer);
        parseToMediaType(buffer, &mt);
        char * resp = "false";
        if(mt.type == ERROR_TYPE)
            resp = "null";
        else 
        {
            free(mt.subtype);
            if(containsMediaType(mediaRange, mt))
                resp = "true";
        }
        printf("%s\n", resp);

        CLEAN_BUFFER
    }
}



