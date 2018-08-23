#include <stdio.h>
#include <stdlib.h>
#include "errorslib.h"

void fail(char * msg) 
{
	fflush(stdout);
	perror(msg);
	exit(1);
}

void checkFail(int aNumber, char * msg)
{
	if (aNumber < 0)
	{
		fail(msg);
	}
}

void checkIsNotNull(void * aPointer, char * msg)
{
	if(aPointer == (void *) 0)
		fail(msg);
}

void checkIsNull(void * aPointer, char * msg)
{
	if(aPointer != (void *) 0)
		fail(msg);
}

void checkAreEquals(int aNumber, int otherNumber, char * msg)
{
	if(aNumber != otherNumber)
		fail(msg);
}

void checkAreNotEqualsWithMsgs(int aNumber, int otherNumber, char * msg1, char * msg2)
{
	if(aNumber == otherNumber)
	{
		printf("%s\n Msg: %s\n", msg1, msg2);
		fail(msg1);
	}
}

