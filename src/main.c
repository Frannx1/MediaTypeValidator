#include <stdio.h>
#include <stdlib.h>
#include "mediaType.h"
#include "mediaRange.h"
#include "mediaTypeParser.h"


#define BUFFER_LENGTH 256

#define CLEAN_BUFFER { int MACc; while ((MACc = getchar()) != '\n' && MACc != EOF); }


void parseAndMapMediaTypes(mediaRangeADT mediaRange, const char ** input, const size_t qty);

void readAndValidateMediaTypes(const mediaRangeADT mediaRange);


int main(int argc, char * argv[])
{
    checkAreEquals(argc, 2, "Invalid Arguments.");
    size_t qty = 0;
    char * input = argv[1];
    char ** splitedInput = splitInput(input, &qty, ',');

    mediaRangeADT mediaRange = createMediaRange();
    parseAndMapMediaTypes(mediaRange, splitedInput, qty);
    readAndValidateMediaTypes(mediaRange);

    return 0;
}

void parseAndMapMediaTypes(mediaRangeADT mediaRange, const char ** input, const size_t qty)
{
    for (int i = 0; i < qty; i++)
    {
        mediaType mt;
        parseToMediaType(input[i], &mt);
        checkNotNull(mt, "Not valid media-type format inserted in the media-range.");
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
        char * resp;
        switch(containsMediaType(mediaRange, mt))
        {
        	case CONTAINS:
        		resp = "true";
        		break;
        	case NOT_CONTAINS:
        		resp = "false";
        		break;	
        	case BAD_FORMAT:
        		resp = "null";
        		break;	
        }
        printf("%s\n");

        CLEAN_BUFFER
    }
}



