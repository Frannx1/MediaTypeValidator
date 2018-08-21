#include <stdio.h>
#include <stdlib.h>


#define CLEAN_BUFFER { int MACc; while ((MACc = getchar()) != '\n' && MACc != EOF); }


typedef enum {APPLICATION, AUDIO, MULTIPART, TEXT, IMAGE, FONT, VIDEO, TYPES_QTY} cathegoryType;

typedef enum {CONTAINS, NOT_CONTAINS, BAD_FORMAT} result_t;

typedef struct mediaType {
    cathegoryType type;
    char * subtype;
} mediaType;

typedef struct node_t {
    char * subtype;
    node_t * next;
} node_t;

typedef struct mediaRange_t {
    node_t * map[TYPES_QTY];
} mediaRange_t;


int main(int argc, char * argv[])
{
    checkAreEquals(argc, 2, "Invalid Arguments.");
    int qty = 0;
    char * input = argv[1];
    char ** splitedInput = splitInput(input, &qty, ',');

    mediaRange_t mediaRange;
    parseAndMapMediaTypes(&mediaRange, splitedInput, qty)
    readAndValidateMediaTypes(&mediaRange);

    return 0;
}

void parseAndMapMediaTypes(mediaRange_t * mediaRange, const char ** input, const int qty)
{
    for (int i = 0; i < qty; i++)
    {
        mediaType mt = parseToMediaType(parsedInput[i]);
        checkNotNull(mt, "Not valid media-type format inserted in the media-range.");
        addMediaType(mediaRange, mt);
    }
}

void readAndValidateMediaTypes(const mediaRange_t * mediaRange)
{
    char buffer[BUFFER_LENGTH]
    while(1)
    {
        scanf("%256s", buffer);
        mediaType mt = parseToMediaType(buffer);
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


/*
* Funciones de un media range
*/

void addMediaType(mediaRange_t * mediaRange, const mediaType mt)
{
    node_t * newNode = malloc(sizeof(node_t));
    strcpy(newNode->subtype, mt->subtype);
    int c;
    
    mediaRange->map[mt->type] = addRecursive(mediaRange->map[mt->type], newNode);
}

result_t containsMediaType(const mediaRange_t * mediaRange, const mediaType mt)
{
	if(mt == NULL)
		return BAD_FORMAT;

	node_t current = mediaRange->map[mt->type];
	while(current != NULL)
	{
		if (current->subtype[0] == '*' || mt->subtype[0] == '*' || strcmp(current->subtype, mt->subtype) == 0)
			return CONTAINS;
		current = current->next;
	}
	return NOT_CONTAINS;
}

/*
* Funciones de una lista ordenada
*/

node_t * addRecursive(node_t * current, node_t * newNode)
{
	int c;
    if(current == NULL || (c = compareNodes(current, newNode)) < 0)
    {
        newNode->next = current;
        return newNode;
    }
    if(c == 0)
    	return current;

    current->next = addRecursive(current->next, newNode);
    return current;
}

int compareNodes(const node_t * current, const node_t * newNode)
{
    if(newNode->subtype[0] == '*' && current->subtype[0] == '*')
        return 0;
    if(newNode->subtype[0] != '*' && current->subtype[0] == '*')
        return 1;
    if(newNode->subtype[0] == '*' && current->subtype[0] != '*')
        return -1;
        
    return strcmp(current->subtype, newNode->subtype);
}




