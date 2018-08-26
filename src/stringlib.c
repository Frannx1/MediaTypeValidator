#include <stdlib.h>
#include "stringlib.h"

#define BLOCK 10


char ** splitString(char * string, size_t * qty, char splitChar)
{
	size_t i = 0, wordSize = 0, respSize = 0;
	char ** resp = malloc(BLOCK * sizeof(*resp));

	while(string[i] != 0)
	{
		if(string[i] == splitChar)
		{
			fixStringSize(&(resp[respSize]), wordSize + 1);
			resp[respSize][wordSize] = 0;
			wordSize = 0;
			i++;
			respSize++;
			checkSize((void **) &resp, respSize, BLOCK, sizeof(*resp));
		}
		else
		{
			checkStringSize(&(resp[respSize]), wordSize, BLOCK);
			resp[respSize][wordSize++] = string[i++];
		}
	}
	fixStringSize(&resp[respSize-1], wordSize + 1);
	resp[respSize][wordSize] = 0;
	respSize++;
	*qty = respSize;
	fixSize((void **) &resp, respSize, sizeof(*resp));
	return resp;
}

void checkStringSize(char ** string, size_t size, size_t block)
{
	checkSize((void **) string, size, block, sizeof(char));
}

void fixStringSize(char ** string, size_t size)
{
	fixSize((void **) string, size, sizeof(char));
}

void checkSize(void ** vec, size_t size, size_t block, size_t nbytes)
{
	if(size == 0)
		*vec = malloc((block) * nbytes);
	else if(size % block == 0)
		*vec = realloc(*vec, (block + size) * nbytes);
}

void fixSize(void ** vec, size_t size, size_t nbytes)
{
	if(size != 0)
		*vec = realloc(*vec, size * nbytes);
}

