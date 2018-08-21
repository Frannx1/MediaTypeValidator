#include <stdlib.h>


#define BLOCK 10


char ** splitInput(char * input, int * qty, char splitChar)
{
	int i, wordSize = 0, respSize = 0;
	char ** resp;

	while(input[i] != 0 && input[i] != '\n')
	{
		if(input[i] == splitChar)
		{
			if(wordSize % BLOCK == 0)
				resp[respSize] = (char *) realloc(resp[respSize], (BLOCK + wordSize) * sizeof(char));
			resp[respSize][wordSize++] = 0;
			resp[respSize] = (char *) realloc(resp[respSize], (wordSize) * sizeof(char));

			if(respSize % BLOCK == 0)
				resp = (char **) realloc(resp, (BLOCK + respSize++) * sizeof(*resp));
		}
		else
		{
			if(wordSize % BLOCK == 0)
				resp[respSize] = (char *) realloc(resp[respSize], (BLOCK + wordSize) * sizeof(char));
			resp[respSize][wordSize++] = input[i++];
		}
	}
	resp = (char **) realloc(resp, (respSize) * sizeof(*resp));
	return resp;
}


